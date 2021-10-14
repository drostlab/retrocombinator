#' Plotting function wrapper
#' @param data Simulation output data obtained from parseEvolutionOutput
#' @param type "initial"  - Plot similarity to initial sequence over time.
#'       "pairwise" - Plot the similarity between sequences over time.
#'       "phylogeny" - Plot the evolution of families over time.
#' @export
plotEvolution <- function(data, type, ...) {
  switch(type,
    initial = plotInitialDistance(data, ...),
    pairwise = plotPairwiseDistance(data, ...),
    families = plotFamilies(data, ...)
  )

}
#' @inherit plotEvolution
plotInitialDistance <- function(data) {
  seqLength <- data$params$SequenceParams_sequenceLength

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
  seqLength <- data$params$SequenceParams_sequenceLength

  to_plot <- data$pairwise %>%
    dplyr::inner_join(data$sequences %>%
                dplyr::select(realTime, sequenceId, isActive) %>%
                dplyr::rename(sequenceId1 = sequenceId, is_active1 = isActive),
              by = c('realTime', 'sequenceId1')) %>%
    dplyr::inner_join(data$sequences %>%
                dplyr::select(realTime, sequenceId, isActive) %>%
                dplyr::rename(sequenceId2 = sequenceId, is_active2 = isActive),
              by = c('realTime', 'sequenceId2')) %>%
    dplyr::mutate(seqSimilarity = 1-distancePairwise/seqLength)

  ggplot2::ggplot(to_plot) +
    ggplot2::geom_point(
      ggplot2::aes(x=realTime, y=seqSimilarity,
                   alpha = 0.2
      )) +
    ggplot2::labs(x = "Time (millions of years)",
                  y = "Pairwise sequence similarity") +
    ggplot2::guides(alpha = FALSE) +
    retrocombinatorTheme()
}

#' @inherit plotEvolution
plotFamilies <- function(data) {
  to_plot <- data$familyRepresentatives %>%
    dplyr::group_by(realTime, familyId) %>%
    dplyr::summarise(numSequences = dplyr::n_distinct(sequenceId),
                     creationTime = min(creationTime))

  ggplot2::ggplot(to_plot, ggplot2::aes(x=realTime, y=familyId)) +
    ggplot2::geom_point(ggplot2::aes(size=numSequences, color=creationTime)) +
    ggplot2::geom_line() +
    ggplot2::labs(x = "Time (millions of years)",
                  y = "Family Id ") +
    ggplot2::scale_size_continuous(
      name ="Number of sequences in family",
    ) +
    retrocombinatorTheme()
}

