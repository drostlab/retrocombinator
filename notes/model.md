### Model

A simulation of the evolution of a set of retrotransposons can be run using
the `simulate()` function. 

The simulation starts with a set of sequences that are either randomly
generated, or read from file. Initially, the entire family of retrotransposons
are assumed to be the exact same sequence.

Retrotransposons are deemed to be *active* by default, and active
retrotransposons are capable of transposition. If the number of active sequences
exceeds a certain threshold, some of them are randomly discarded, to simulate
extinction events until the total number of copies is within the specified
limit.


```
sequenceParams <- SequenceParams(num_initial_copies = 100, 
                                 seq_length = 5000)

simulationParams <- SimulationParams(num_jumps = 20,
                                     timestep = 1,
                                     max_active_copies = 500)
```

During the simulation, each retrotransposon sequence undergoes point mutations
under one of six nucleotide substitution models.

```
mutationParams <- MutationParams(model = 'K80') 
```

If due to a point mutation, a retrotransposon if affected in a critical region,
it might become inactive with a specified probability. If the number of inactive
sequences exceeds a threshold, they are discarded in a similar fashion to how
active sequences are discarded.

```
flagParams <- FlagParams(length_critical_region = 100,
                         prob_inactive_when_mutated = 0.001,
                         max_inactive_copies = 500)
```

During a transposition (burst event) a retrotransposon increases in copy number.
This happens with a specified probability. This package is capable of simulating
the burst events under two assumptions - (a) without recombination, where each
bursting sequence is copied directly (b) with recombination, where each
bursting sequence recombines with another similar sequence before it inserts
itself back into the genome. 

```
burstParams <- BurstParams(burst_probability = 0.1,
                           burst_mean = 1,
                           recomb_mean = 1.5
                           recomb_similarity = 0.85)
```

During the simulation, sequences that diverge from the initial sequence by a
large amount can be discarded to simulate evolutionary pressure. Similarly,
speciation events can be simulated by allowing the set of sequences to split
into two species, where retrotransposons from different species are not allowed
to recombine with each other during transposition.

```
speciesParams <- SpeciesParams(selection_threshold = 0.5,
                               species_similarity = 0.7,
                               species_coherence = 0.5)
```

### I/O examples


