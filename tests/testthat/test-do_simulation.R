context("do_simulation_r")

test_that("data type", {
  n_generations <- 0
  df <- do_simulation_r(
    max_genetic_distance = 1,
    n_generations = 0,
    n_pin = 1,
    n_sil = 1,
    pin_mutation_rate = 0.1,
    population_size = 1,
    results_filename = "results.csv",
    rng_seed = 42,
    sampling_interval = 1,
    sil_mutation_rate = 0.1
  )
  expect_equal(class(df) == "data.frame", TRUE)
  expect_equal(nrow(df), n_generations)
  expect_equal(ncol(df), 2)

})