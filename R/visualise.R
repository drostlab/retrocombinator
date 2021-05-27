#' Plotting function wrapper
#' @param data Simulation output data obtained from parseEvolutionOutput
#' @param type "initial"  - Plot similarity to initial sequence over time.
#'       "pairwise" - Plot the similarity between sequences over time.
#'       "phylogeny" - Plot the evolution of species over time.
#' @export
plotEvolution <- function(data, type, ...) {
  switch(type,
    initial = plotInitialDistance(data, ...),
    pairwise = plotPairwiseDistance(data, ...),
    phylogeny = plotPhylogeny(data, ...)
  )

}
#' @inherit plotEvolution
plotInitialDistance <- function(data) {
  seqLength <- data$sequences %>%
    dplyr::filter(step == 0) %>%
    dplyr::pull(rawSequence) %>% nchar() %>% mean()

  to_plot <- data$sequences %>%
    dplyr::mutate(seqSimilarity = 1-distanceToInitial/seqLength)

  ggplot2::ggplot(
      to_plot,
      ggplot2::aes(x=realTime, y=seqSimilarity,
                   group=sequenceId,
                   color=isActive,
                   alpha=0.05)
    ) +
    ggplot2::geom_line() +
    ggplot2::labs(x = "Time (millions of years)",
                  y = "Similarity to initial sequence") +
    ggplot2::scale_color_manual(
      name = "Capable of transposition events (active status)",
      values = c("TRUE" = "lightblue", "FALSE" = "salmon")
    ) +
    ggplot2::guides(alpha = FALSE) +
    retrocombinatorTheme()
}

#' @inherit plotEvolution
plotPairwiseDistance <- function(data) {
  seqLength <- data$sequences %>%
    dplyr::filter(step == 0) %>%
    dplyr::pull(rawSequence) %>% nchar() %>% mean()

  speciesAges <- data$sequences %>%
    dplyr::group_by(speciesId) %>%
    dplyr::summarise(speciesBirth = min(realTime))

  to_plot <- data$pairwise %>%
    dplyr::inner_join(data$sequences %>%
                dplyr::select(realTime, sequenceId, speciesId, isActive) %>%
                dplyr::rename(sequenceId1 = sequenceId, speciesId1 = speciesId, is_active1 = isActive),
              by = c('realTime', 'sequenceId1')) %>%
    dplyr::inner_join(data$sequences %>%
                dplyr::select(realTime, sequenceId, speciesId, isActive) %>%
                dplyr::rename(sequenceId2 = sequenceId, speciesId2 = speciesId, is_active2 = isActive),
              by = c('realTime', 'sequenceId2')) %>%
    dplyr::mutate(sameSpecies = speciesId1 == speciesId2) %>%
    dplyr::mutate(groupSpecies = paste(speciesId1, speciesId2, sep="_")) %>%
    dplyr::mutate(seqSimilarity = 1-distancePairwise/seqLength) %>%
    dplyr::left_join(speciesAges %>% dplyr::rename(speciesId1 = speciesId, birth1 = speciesBirth),
                     by = 'speciesId1') %>%
    dplyr::left_join(speciesAges %>% dplyr::rename(speciesId2 = speciesId, birth2 = speciesBirth),
                     by = 'speciesId2') %>%
    dplyr::mutate(age1 = realTime - birth1) %>%
    dplyr::mutate(age2 = realTime - birth2) %>%
    dplyr::mutate(age = ifelse(age1 > age2, age1, age2))

  ggplot2::ggplot(to_plot) +
    ggplot2::geom_point(
      ggplot2::aes(x=realTime, y=seqSimilarity,
                   #group = group_fam,
                   #linetype=is_active,
                   color=sameSpecies,
                   size = age,
                   alpha = 0.2
      )) +
    ggplot2::labs(x = "Time (millions of years)",
                  y = "Pairwise sequence similarity") +
    ggplot2::scale_color_manual(
      name = "Pair within the same species)",
      values = c("TRUE" = "lightblue", "FALSE" = "salmon")
    ) +
    ggplot2::scale_size_continuous(name = "Age of species (millions of years)") +
    ggplot2::guides(alpha = FALSE) +
    retrocombinatorTheme()
}

#' @inherit plotEvolution
plotPhylogeny <- function(data) {
  to_plot <- data$sequences %>%
    dplyr::select(-rawSequence) %>%
    dplyr::mutate(speciesId = as.factor(speciesId)) %>%
    dplyr::group_by(realTime, speciesId) %>%
    dplyr::summarise(numSequences = dplyr::n_distinct(sequenceId))

  ggplot2::ggplot(to_plot, ggplot2::aes(x=realTime, y=speciesId)) +
    ggplot2::geom_point(ggplot2::aes(size=numSequences)) +
    ggplot2::geom_line() +
    ggplot2::labs(x = "Time (millions of years)",
                  y = "Species Id ") +
    ggplot2::scale_size_continuous(
      name ="Number of sequences in species",
    ) +
    #ggplot2::guides(color = FALSE) +
    retrocombinatorTheme()
}

plotSpeciesComparison <- function(data) {
  seqLength <- data$sequences %>%
    dplyr::filter(step == 0) %>%
    dplyr::pull(rawSequence) %>% nchar() %>% mean()

  speciesDistance <- data$pairwise %>%
    dplyr::left_join(data$sequences %>% dplyr::select(sequenceId, speciesId) %>% dplyr::rename(sequenceId1=sequenceId, speciesId1=speciesId)) %>%
    dplyr::left_join(data$sequences %>% dplyr::select(sequenceId, speciesId) %>% dplyr::rename(sequenceId2=sequenceId, speciesId2=speciesId)) %>%
    dplyr::group_by(realTime, speciesId1, speciesId2) %>%
    dplyr::summarise(aggregatedDistanceMin = min(distancePairwise),
                     aggregatedDistanceMax = max(distancePairwise)
                     ) %>%
    dplyr::mutate(
      aggregatedSimilarityMax = 1-aggregatedDistanceMin/seqLength,
      aggregatedSimilarityMin = 1-aggregatedDistanceMax/seqLength
    )

  to_plot <- speciesDistance %>%
    dplyr::filter(realTime == max(speciesDistance$realTime))

  ggplot2::ggplot(to_plot) +
    ggplot2::geom_point(ggplot2::aes(
      x=speciesId1, y=speciesId2,
      size=aggregatedSimilarityMax,
      color = "red",
      alpha=0.3
    )) +
    ggplot2::geom_point(ggplot2::aes(
      x=speciesId2, y=speciesId1,
      size=aggregatedSimilarityMax,
      color = "red",
      alpha=0.3
    )) +
    ggplot2::geom_point(ggplot2::aes(
      x=speciesId1, y=speciesId2,
      size=aggregatedSimilarityMin,
      color = "blue",
      alpha=0.3
    )) +
    ggplot2::geom_point(ggplot2::aes(
      x=speciesId2, y=speciesId1,
      size=aggregatedSimilarityMin,
      color = "blue",
      alpha=0.3
    )) +
    ggplot2::labs(x = "SpeciesId1",
                  y = "SpeciesId2 ") +
    ggplot2::scale_size_continuous(
      name ="Mean similarity between species",
      breaks = c(0.3, 0.6, 0.9),
      limits = c(0, 1.0),
      range = c(0, 6)
    ) +
    ggplot2::guides(alpha = FALSE)
    #retrocombinatorTheme()
}
