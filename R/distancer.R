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
#' @param sampling_interval how often is the species abundances measured?
#' @return Timepoints when there were new species
#' @export
do_simulation_r <- function(
  max_genetic_distance,
  mutation_rate,
  n_generations,
  n_loci,
  population_size,
  rng_seed,
  sampling_interval
  ) {

  do_simulation_cpp(
    max_genetic_distance,
    mutation_rate,
    n_generations,
    n_loci,
    population_size,
    rng_seed,
    sampling_interval
)
  df <- read.table("results.csv", header = TRUE, sep = ",")
  #df <- read.table("~/GitHubs/distancer/vignettes/results.csv", header = TRUE, sep = ",")
  #colnames(df)
  #print(df)
  df
}