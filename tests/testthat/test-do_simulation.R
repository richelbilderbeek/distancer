context("do_simulation_r")

test_that("data type", {
  n_generations <- 0
  df <- do_simulation_r(
    max_genetic_distance = 1,
    mutation_rate = 0.1,
    n_generations = 0,
    n_loci = 1,
    population_size = 1,
    rng_seed = 42,
    sampling_interval = 1
  )
  expect_equal(class(df) == "data.frame", TRUE)
  expect_equal(nrow(df), n_generations)
  expect_equal(ncol(df), 2)

})

test_that("In zero generations, there will be only one species", {
  n_generations <- 0
  df <- do_simulation_r(
    max_genetic_distance = 1,
    mutation_rate = 0.1,
    n_generations = 0,
    n_loci = 1,
    population_size = 1,
    rng_seed = 42,
    sampling_interval = 1
  )
  expect_equal(nrow(df), n_generations)
})

test_that("In 10000 generations, there will be 10000 rows", {
  n_generations <- 10000
  df <- do_simulation_r(
    max_genetic_distance = 1,
    mutation_rate = 0.1,
    n_generations = 10000,
    n_loci = 1,
    population_size = 1,
    rng_seed = 42,
    sampling_interval = 1
  )
  expect_equal(nrow(df), n_generations)
})

