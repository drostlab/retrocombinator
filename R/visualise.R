#' Plot distance to initial sequence
#' @param data Simulation data obtained using `input_data`
#' @export
plot_initial_distances <- function(data) {
  seq_length <- data$init %>%
    dplyr::filter(step == 0) %>%
    dplyr::pull(raw) %>% nchar() %>% mean()

  to_plot <- data$init %>%
    dplyr::mutate(init_seq_similarity = 1-init_dist/seq_length)
  ggplot2::ggplot(to_plot) +
    ggplot2::geom_line(
      ggplot2::aes(x=real_time, y=init_seq_similarity,
                   group=seq_tag,
                   color=is_active,
                   alpha=0.3
      )) +
  ggplot2::labs(x = "Time (millions of years)",
                y = "Similarity to initial sequence") +
  ggplot2::scale_color_discrete(name = "Capable of transposition events") +
  ggplot2::guides(alpha = FALSE)
}

#' Plot pairwise distance within families
#' @param data Simulation data obtained using `input_data`
#' @export
plot_family_distances <- function(data) {
  seq_length <- data$init %>%
    dplyr::filter(step == 0) %>%
    dplyr::pull(raw) %>% nchar() %>% mean()

  to_plot <- data$pair %>%
    dplyr::inner_join(data$init %>%
                dplyr::select(real_time, seq_tag, fam_tag, is_active) %>%
                dplyr::rename(seq1 = seq_tag, fam1 = fam_tag, is_active1 = is_active),
              by = c('real_time', 'seq1')) %>%
    dplyr::inner_join(data$init %>%
                dplyr::select(real_time, seq_tag, fam_tag, is_active) %>%
                dplyr::rename(seq2 = seq_tag, fam2 = fam_tag, is_active2 = is_active),
              by = c('real_time', 'seq2')) %>%
    dplyr::mutate(same_family = fam1 == fam2) %>%
    dplyr::mutate(group_fam = paste(fam1, fam2, sep="_")) %>%
    dplyr::mutate(seq_similarity = 1-dist/seq_length)

  ggplot2::ggplot(to_plot) +
    ggplot2::geom_point(
      ggplot2::aes(x=real_time, y=seq_similarity,
                   group = group_fam,
                   #linetype=is_active,
                   color=same_family
      )) +
  ggplot2::labs(x = "Time (millions of years)",
                y = "Pairwise sequence similarity") +
  ggplot2::scale_color_discrete(name = "Within same Family")
}

#' Plot mosaic of recombination
#' @param data Simulation data obtained using `input_data`
#' @export
plot_phylogeny <- function(data) {
  to_plot <- data$init %>%
    dplyr::select(-raw)
  starting <- to_plot %>%
    dplyr::select(step == 0) %>%
    pull(seq_tag)
}

#' Plot families over time
#' @param data Simulation data obtained using `input_data`
#' @export
plot_phylogeny <- function(data) {
  to_plot <- data$init %>%
    dplyr::select(-raw) %>%
    dplyr::mutate(fam_tag = as.factor(fam_tag)) %>%
    dplyr::mutate(fam_par = as.factor(fam_par))
  #families <- to_plot %>% dplyr::pull(fam_tag) %>% unique()

  ggplot2::ggplot(to_plot, ggplot2::aes(x=real_time, y=fam_tag, color = fam_par)) +
    ggplot2::geom_line() +
    ggplot2::labs(x = "Time (millions of years)",
                  y = "Family ") +
    ggplot2::scale_color_discrete(name = "Original family")
}
