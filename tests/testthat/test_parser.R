context("Reading output of C++ simulation")

test_that("Parsing the C++ simulation output works", {
  run <- parseSimulationOutput(system.file("testdata", "test_simulation.test",
                                           package="retrocombinator"))
  expected <- readRDS(system.file("testdata", "test_parser_expected.rds",
                                  package="retrocombinator"))

  expect_equal(run$params, expected$params)
  expect_equal(run$sequences, expected$sequences)
  expect_equal(run$pairwise, expected$pairwise)
  expect_equal(run$familyRepresentatives, expected$familyRepresentatives)
  expect_equal(run$familyPairwise, expected$familyPairwise)
})
