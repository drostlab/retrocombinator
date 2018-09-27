#' Input data from CPP output into a set of R data frames
#' @importFrom magrittr "%>"
#' @export
input_data <- function(filename)
{
  data <- list()
  # TODO: extract parameters and store in the same dataframe
  data$params <- c()
  data$init <- data.frame()
  data$pair <- data.frame()

  con = file(filename, "r")

  # basic variables
  t <- -1
  real_time <- -1
  tags <- NULL

  while (TRUE)
  {
    # try and extract the next block of data
    next_line = extract_line(con)

    if (length(next_line) == 0) # end of file
    {
      break
    }
    if (next_line[1] == "0") # header info
    {
      next
    }
    if (next_line[1] == "@")
    {
      # First, get the time
      time_line <- as.numeric(extract_line(con))
      t <- time_line[1]
      print(paste("Time", t))
      real_time <- time_line[2]

      # Get which things are going to be output
      which_output_line <- as.numeric(extract_line(con))
      to_tags <- which_output_line[1]
      to_init <- which_output_line[2]
      to_seqs <- which_output_line[3]
      to_pair <- which_output_line[4]

      family_line <- extract_line(con)
      stopifnot(family_line[1] == "F")
      family_line <- extract_line(con)
      num_families <- as.numeric(family_line[1])

      # To store the tags in memory
      fam_tags <- integer(num_families)
      fam_par_tags <- integer(num_families)
      seq_tags <- list()

      if (num_families == 0)
      {
        if (to_pair)
        {
          pairs_line <- extract_line(con)
          stopifnot(pairs_line[1] == "P")
          blank_line <- extract_line(con)
        }
        next
      }

      # For each family, parse all the data
      for (fam_i in 1:num_families)
      {
        family_tag_line <- extract_line(con)
        fam_tags[fam_i] <- as.numeric(family_tag_line)[1]
        fam_par_tags[fam_i] <- as.numeric(family_tag_line)[2]

        tags_line <- extract_line(con)

        stopifnot(tags_line[1] == "T")
        tags_line <- extract_line(con)
        num_seqs <- tags_line[1]
        all_seqs <- extract_line(con)

        # Extract sequence tag data
        seq_tags[[fam_i]] <- integer(num_seqs)
        p1 <- integer(num_seqs)
        p2 <- integer(num_seqs)
        is_active <- logical(num_seqs)

        for (seq_i in 1:num_seqs)
        {
          parsed_seq <- strsplit(
                          gsub("\\*|\\)|\\(|-|\\/", " ", all_seqs[seq_i]),
                          " ")[[1]]
          seq_tags[[fam_i]][seq_i] <- as.numeric(parsed_seq[1])

          # Make -1 denote initial sequence
          if (parsed_seq[3] == "I" || parsed_seq[3] == "R")
          {
             p1[seq_i] <- -1
             p2[seq_i] <- -1
          }
          else
          {
             p1[seq_i] <- as.numeric(parsed_seq[3])
             p2[seq_i] <- as.numeric(parsed_seq[4])
          }
          is_active[seq_i] <- stringr::str_detect(all_seqs[seq_i], "\\*")
        }

        if (to_init)
        {
          init_line <- extract_line(con)
          stopifnot(init_line[1] == "I")
          # Extract distance to initial sequence
          init_line <- extract_line(con)
          init_dists <- as.numeric(init_line)
          for (seq_i in 1:num_seqs)
          {
            row <- list(step=t, real_time=real_time,
                        seq=seq_tags[[fam_i]][seq_i],
                        fam=fam_tags[fam_i], fam_par=fam_par_tags[fam_i],
                        p1=p1[seq_i], p2=p2[seq_i], is_active=is_active[seq_i],
                        init_dist=init_dists[seq_i], raw=NA)
            data$init <- rbind(data$init, row)
          }
        }

        if (to_seqs)
        {
          seqs_line <- extract_line(con)
          stopifnot(seqs_line[1] == "S")
          # Extract raw sequence
          for (seq_i in 1:num_seqs)
          {
            raw_seq <- extract_line(con)
            found <- which(data$init$step == t & data$init$seq==seq_tags[[fam_i]][seq_i],
                           arr.ind = TRUE)
            data$init[found, ]$raw  <- raw_seq
          }
        }
      } # End 'for each family'

      if (to_pair)
      {
        pairs_line <- extract_line(con)
        stopifnot(pairs_line[1] == "P")
        # Pairwise distances
        pairs <- as.numeric(extract_line(con))
        count <- 1

        f1 <- 1 # Family F1
        while (f1 <= length(fam_tags))
        {
          s1 <- 1 # Sequence S1
          while (s1 <= length(seq_tags[[f1]]))
          {
            s2 <- s1 + 1 # Sequence S2 in F1
            while (s2 <= length(seq_tags[[f1]]))
            {
              row <- list(step=t, real_time=real_time,
                          seq1=seq_tags[[f1]][s1], seq2=seq_tags[[f1]][s2],
                          pair=pairs[count])
              count <- count + 1
              data$pair <- rbind(data$pair, row)
              s2  <- s2 + 1
            }

            f2 <- f1 + 1 # Family F2
            while (f2 <= length(fam_tags))
            {
              s2 <- 1 # Sequence S2 in F2
              while (s2 <= length(seq_tags[[f2]]))
              {
                row <- list(step=t, real_time=real_time,
                            seq1=seq_tags[[f1]][s1], seq2=seq_tags[[f2]][s2],
                            pair=pairs[count])
                count <- count + 1
                data$pair <- rbind(data$pair, row)
                s2 <- s2 + 1
              }
              f2 <- f2 + 1
            }
            s1 <- s1 + 1
          }
          f1 <- f1 + 1
        } # end <for family F1>

      } # end <extract pair data>
    } # end <for this timestamp>
    else
    {
        stop(paste("Unknown letter in file", next_line[2]))
    }
  } # end <for this file>

  close(con)

  return(data)
}

# To extract the next line from the file
extract_line <- function(in_file)
{
  line = readLines(in_file, n=1)
  if (length(line) == 0) { return(c()) }
  return(strsplit(line, " ")[[1]])
}

