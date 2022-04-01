isSemiPositiveNumber <- function(n) {
  is.numeric(n) && n >= 0
}
isPositiveNumber <- function(n) {
  is.numeric(n) && n > 0
}
isProbability <- function(n) {
  is.numeric(n) && n >= 0 && n <= 1
}

#' A basic ggplot2 theme for consistent aesthetic
#' @export
retrocombinatorTheme <- function() {
  ggplot2::theme(
    legend.position = "bottom",
    legend.direction = "vertical"
  )
}
