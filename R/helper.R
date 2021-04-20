isPositiveNumber <- function(n) {
  is.numeric(n) && n > 0
}
isProbability <- function(n) {
  is.numeric(n) && n >= 0 && n <= 1
}
