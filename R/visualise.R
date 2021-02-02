#' Plot distance to initial sequence
#' @param data Simulation data obtained using `input_data`
#' @export
plot_initial_distances <- function(data) {
  to_plot <- data$init
  to_plot$fam_tag <- as.factor(to_plot$fam_tag)
  ggplot2::ggplot(to_plot) +
    ggplot2::geom_line(
      ggplot2::aes(x=real_time, y=init_dist,
                   group=seq_tag,
                   #linetype=is_active,
                   color=fam_tag
      )) +
  ggplot2::labs(x = "Time (millions of years)",
                y = "Distance to initial sequence") +
  ggplot2::scale_color_discrete(name = "Family")
}

#' Plot pairwise distance within families
#' @param data Simulation data obtained using `input_data`
#' @export
plot_family_distances <- function(data) {
  to_plot <- data$pair %>%
    dplyr::inner_join(data$init %>%
                dplyr::select(real_time, seq_tag, fam_tag, is_active) %>%
                dplyr::rename(seq1 = seq_tag, fam1 = fam_tag, is_active1 = is_active),
              by = c('real_time', 'seq1')) %>%
    dplyr::inner_join(data$init %>%
                dplyr::select(real_time, seq_tag, fam_tag, is_active) %>%
                dplyr::rename(seq2 = seq_tag, fam2 = fam_tag, is_active2 = is_active),
              by = c('real_time', 'seq2'))

  to_plot <- to_plot %>%
    dplyr::mutate(same_family = fam1 == fam2) %>%
    dplyr::mutate(group_fam = paste(fam1, fam2, sep="_"))
  ggplot2::ggplot(to_plot) +
    ggplot2::geom_point(
      ggplot2::aes(x=real_time, y=dist,
                   group = group_fam,
                   #linetype=is_active,
                   color=same_family
      )) +
  ggplot2::labs(x = "Time (millions of years)",
                y = "Pairwise distance") +
  ggplot2::scale_color_discrete(name = "Within same Family")
}
