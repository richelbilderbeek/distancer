#' @useDynLib distancer
#' @importFrom Rcpp sourceCpp
NULL

#' The function that does a simulation.
#' @param max_genetic_distance the maximum number of different loci that two individuals can still produce viable offspring with
#' @param mutation_rate DNA mutation rate
#' @param n_generations number of generations
#' @param n_pin number of Phylogeny Inference Nucleotides
#' @param n_sil number of Species Identity Loci
#' @param population_size population size
#' @param result_filename name of the file the results will be written to
#' @param rng_seed random number generator seed
#' @param sampling_interval how often is the species abundances measured?
#' @return Timepoints when there were new species
#' @export
do_simulation_r <- function(
  max_genetic_distance,
  mutation_rate,
  n_generations,
  n_pin,
  n_sil,
  population_size,
  results_filename,
  rng_seed,
  sampling_interval
  ) {

  do_simulation_cpp(
    max_genetic_distance,
    mutation_rate,
    n_generations,
    n_pin,
    n_sil,
    population_size,
    results_filename,
    rng_seed,
    sampling_interval
)
  df <- read.table(results_filename, header = TRUE, sep = ",")
  #df <- read.table("~/GitHubs/distancer/vignettes/results.csv", header = TRUE, sep = ",")
  #colnames(df)
  #print(df)
  df
}