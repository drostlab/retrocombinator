isPositiveNumber <- function(n) {
  is.numeric(n) && n > 0
}
isProbability <- function(n) {
  is.numeric(n) && n >= 0 && n <= 1
}

retrocombinatorTheme <- function() {
  ggplot2::theme(
    legend.position = "bottom",
    legend.direction = "vertical"
  )
}
