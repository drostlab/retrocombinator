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
                   alpha=0.2)
    ) +
    ggplot2::geom_line() +
    ggplot2::geom_point() +
    ggplot2::labs(x = "Time (millions of years)",
                  y = "Similarity to initial sequence") +
    ggplot2::scale_color_manual(
      name = "Capable of transposition events (active status)",
      values = c("TRUE" = "blue", "FALSE" = "red")
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
      values = c("TRUE" = "blue", "FALSE" = "red")
    ) +
    ggplot2::scale_size_continuous(name = "Age of species (millions of years)") +
    ggplot2::guides(alpha = FALSE) +
    retrocombinatorTheme()
}

#' @inherit plotEvolution
plotPhylogeny <- function(data) {
  to_plot <- data$sequences %>%
    dplyr::select(-raw) %>%
    dplyr::mutate(fam_tag = as.factor(fam_tag)) %>%
    dplyr::mutate(fam_par = as.factor(fam_par))
  #families <- to_plot %>% dplyr::pull(fam_tag) %>% unique()

  ggplot2::ggplot(to_plot, ggplot2::aes(x=real_time, y=fam_par, color = fam_tag)) +
    ggplot2::geom_line() +
    ggplot2::labs(x = "Time (millions of years)",
                  y = "Family ") +
    ggplot2::scale_color_discrete(name = "Original family") +
    ggplot2::geom_line(ggplot2::aes(x=real_time, y=fam_tag, color = fam_par)) +
    ggplot2::guides(color = FALSE) +
    retrocombinatorTheme()
}
