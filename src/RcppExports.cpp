// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// do_simulation_cpp
void do_simulation_cpp(const int max_genetic_distance, const int n_generations, const int n_pin, const int n_sil, const double pin_mutation_rate, const int population_size, const std::string& results_filename, const int rng_seed, const int sampling_interval, const double sil_mutation_rate);
RcppExport SEXP distancer_do_simulation_cpp(SEXP max_genetic_distanceSEXP, SEXP n_generationsSEXP, SEXP n_pinSEXP, SEXP n_silSEXP, SEXP pin_mutation_rateSEXP, SEXP population_sizeSEXP, SEXP results_filenameSEXP, SEXP rng_seedSEXP, SEXP sampling_intervalSEXP, SEXP sil_mutation_rateSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< const int >::type max_genetic_distance(max_genetic_distanceSEXP);
    Rcpp::traits::input_parameter< const int >::type n_generations(n_generationsSEXP);
    Rcpp::traits::input_parameter< const int >::type n_pin(n_pinSEXP);
    Rcpp::traits::input_parameter< const int >::type n_sil(n_silSEXP);
    Rcpp::traits::input_parameter< const double >::type pin_mutation_rate(pin_mutation_rateSEXP);
    Rcpp::traits::input_parameter< const int >::type population_size(population_sizeSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type results_filename(results_filenameSEXP);
    Rcpp::traits::input_parameter< const int >::type rng_seed(rng_seedSEXP);
    Rcpp::traits::input_parameter< const int >::type sampling_interval(sampling_intervalSEXP);
    Rcpp::traits::input_parameter< const double >::type sil_mutation_rate(sil_mutation_rateSEXP);
    do_simulation_cpp(max_genetic_distance, n_generations, n_pin, n_sil, pin_mutation_rate, population_size, results_filename, rng_seed, sampling_interval, sil_mutation_rate);
    return R_NilValue;
END_RCPP
}
