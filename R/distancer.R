#' @useDynLib distancer
#' @importFrom Rcpp sourceCpp
NULL

#' The function that does a simulation.
#' @param max_genetic_distance the maximum number of different loci that two individuals can still produce viable offspring with
#' @param n_generations number of generations
#' @param n_pin number of Phylogeny Inference Nucleotides
#' @param n_sil number of Species Identity Loci
#' @param pin_mutation_rate PIN mutation rate
#' @param population_size population size
#' @param result_filename name of the file the results will be written to
#' @param rng_seed random number generator seed
#' @param sampling_interval how often is the species abundances measured?
#' @param sil_mutation_rate SIL mutation rate
#' @return Timepoints when there were new species
#' @export
do_simulation_r <- function(
  max_genetic_distance,
  n_generations,
  n_pin,
  n_sil,
  pin_mutation_rate,
  population_size,
  results_filename,
  rng_seed,
  sampling_interval,
  sil_mutation_rate
  ) {

  do_simulation_cpp(
    max_genetic_distance,
    n_generations,
    n_pin,
    n_sil,
    pin_mutation_rate,
    population_size,
    results_filename,
    rng_seed,
    sampling_interval,
    sil_mutation_rate
)
  df <- read.table(results_filename, header = TRUE, sep = ",")
  #df <- read.table("~/GitHubs/distancer/vignettes/results.csv", header = TRUE, sep = ",")
  #colnames(df)
  #print(df)
  df
}