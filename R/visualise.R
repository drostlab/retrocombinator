#' Plotting function wrapper
#' @param data Simulation output data obtained from [retrocombinator::parseEvolutionOutput()()]
#' @param type What should be plotted?
#' \describe{
#' \item{"initial"}{Plot similarity to initial sequence over time.}
#' \item{"pairwise"}{Plot the similarity between sequences over time.}
#' \item{"families"}{Plot the evolution of families over time.}
#' }
#' @param ... Any additional arguments to pass to specialised plotting functions
#'        (currently unused)
#' @return A corresponding evolutionary history plot, based on the simulation of
#'         the evolution of retrotransposons
#' @examples
#' \dontrun{
#' plotEvolution(myData, "initial")
#' }
#' @export
plotEvolution <- function(data, type, ...) {
  switch(type,
    initial = plotInitialDistance(data, ...),
    pairwise = plotPairwiseDistance(data, ...),
    families = plotFamilies(data, ...)
  )
}

plotInitialDistance <- function(data) {
  seqLength <- data$params$SequenceParams_sequenceLength

  to_plot <- data$sequences %>%
    dplyr::mutate(seqSimilarity = 1-.data$distanceToInitial/seqLength)

  ggplot2::ggplot(
      to_plot,
      ggplot2::aes(x=.data$realTime, y=.data$seqSimilarity,
                   group=.data$sequenceId,
                   color=.data$isActive,
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


plotPairwiseDistance <- function(data) {
  seqLength <- data$params$SequenceParams_sequenceLength

  to_plot <- data$pairwise %>%
    dplyr::inner_join(data$sequences %>%
                dplyr::select(.data$realTime, .data$sequenceId, .data$isActive) %>%
                dplyr::rename(sequenceId1 = .data$sequenceId, is_active1 = .data$isActive),
              by = c('realTime', 'sequenceId1')) %>%
    dplyr::inner_join(data$sequences %>%
                dplyr::select(.data$realTime, .data$sequenceId, .data$isActive) %>%
                dplyr::rename(sequenceId2 = .data$sequenceId, is_active2 = .data$isActive),
              by = c('realTime', 'sequenceId2')) %>%
    dplyr::mutate(seqSimilarity = 1-.data$distancePairwise/seqLength)

  ggplot2::ggplot(to_plot) +
    ggplot2::geom_point(
      ggplot2::aes(x=.data$realTime, y=.data$seqSimilarity,
                   alpha = 0.2
      )) +
    ggplot2::labs(x = "Time (millions of years)",
                  y = "Pairwise sequence similarity") +
    ggplot2::guides(alpha = FALSE) +
    retrocombinatorTheme()
}


plotFamilies <- function(data) {
  to_plot <- data$familyRepresentatives %>%
    dplyr::mutate(familyId = factor(.data$familyId)) %>%
    dplyr::group_by(.data$realTime, .data$familyId) %>%
    dplyr::summarise(numSequences = dplyr::n_distinct(.data$sequenceId),
                     creationTime = min(.data$creationTime))

  ggplot2::ggplot(to_plot, ggplot2::aes(x=.data$realTime, y=.data$familyId)) +
    ggplot2::geom_point(ggplot2::aes(size=.data$numSequences, color=.data$creationTime)) +
    ggplot2::geom_line() +
    ggplot2::labs(x = "Time (millions of years)",
                  y = "Family Id ") +
    ggplot2::scale_size_continuous(
      name ="Number of sequences in family",
    ) +
    retrocombinatorTheme()
}


# plotFamiliesPairwise <- function(data) {
#  seqLength <- data$params$SequenceParams_sequenceLength
#  maxRealTime <- max(data$familyRepresentatives$realTime)
#
#  halfData <- data$familyPairwise %>%
#    dplyr::filter(.data$realTime == maxRealTime)
#
#  fullData <- halfData %>%
#    rbind(data.frame(step = halfData$step,
#                     realTime = halfData$realTime,
#                     familyId1 = halfData$familyId2,
#                     familyId2 = halfData$familyId1,
#                     distancePairwise = halfData$distancePairwise))
#
#  familyIdLevels <- unique(sort(fullData$familyId1))
#  to_plot <- fullData %>%
#    dplyr::mutate(familyId1 = factor(.data$familyId1, levels = familyIdLevels)) %>%
#    dplyr::mutate(familyId2 = factor(.data$familyId2, levels = familyIdLevels)) %>%
#    dplyr::mutate(seqSimilarity = 1-.data$distancePairwise/seqLength)
#
#  ggplot2::ggplot(to_plot) +
#    ggplot2::geom_point(
#      ggplot2::aes(x=.data$familyId1, y=.data$familyId2,
#                   size = .data$seqSimilarity
#      )) +
#    ggplot2::labs(x = "Family Id",
#                  y = "Family Id") +
#    ggplot2::scale_size_continuous(
#      name ="Sequence similarity"
#    ) +
#    retrocombinatorTheme()
#}

