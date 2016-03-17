#' @useDynLib distancer
#' @importFrom Rcpp sourceCpp
NULL

#' The function that does a simulation.
#' @param max_genetic_distance the maximum number of different loci that two individuals can still produce viable offspring with
#' @param mutation_rate DNA mutation rate
#' @param n_generations number of generations
#' @param n_loci number of loci
#' @param population_size population size
#' @param rng_seed random number generator seed
#' @return Timepoints when there were new species
#' @export
do_simulation_r <- function(
  max_genetic_distance,
  mutation_rate,
  n_generations,
  n_loci,
  population_size,
  rng_seed
  ) {

  ts <- do_simulation_cpp(
    max_genetic_distance,
    mutation_rate,
    n_generations,
    n_loci,
    population_size,
    rng_seed
  )

  ns <- seq(1,length(ts))
  df <- data.frame(ns = ns, ts = ts)
  df
}