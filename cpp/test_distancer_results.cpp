#include "distancer_results.h"
#include <fstream>
#include <boost/test/unit_test.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "distancer_population_factory.h"
#include "is_regular_file.h"
#include "convert_dot_to_svg.h"
#include "convert_svg_to_png.h"

// From a population, create a single node phylogeny:
//
// +----+
// | 00 | <- SIL
// | 02 | <- frequency
// +----+
BOOST_AUTO_TEST_CASE(test_results_create_single_node_phylogeny)
{
  const int max_genetic_distance{1};
  results r(max_genetic_distance);
  const pin my_pin("");
  const sil my_sil(2, 0b00);
  std::vector<individual> p{
    individual(my_pin, my_sil)
  };

  r.add_measurement(0, p);

  const auto g = r.get_sil_frequency_phylogeny();
  BOOST_CHECK_EQUAL(boost::num_vertices(g), 1);
  BOOST_CHECK_EQUAL(g[*vertices(g).first].get_sil_frequencies().size(), 1);
}

/*

The initial state in data collection looks as such:

```
+--+--+--+--+--+--+--+--+--+--+
|G |t1|t2|t3|t4|t5|t6|t7|t8|t9|
+--+--+--+--+--+--+--+--+--+--+
|00| 9| 8| 6| 5| 4| 4| 4| 4| 4|
|01|  | 1| 2| 2| 2| 1|  |  |  |
|11|  |  | 1| 2| 3| 4| 5| 5| 5|
|10|  |  |  |  |  |  |  |  |  |
+--+--+--+--+--+--+--+--+--+--+
```

Next step: create a graph from this:

```
     9--8--6--5--4--4--4--4--4
        1--2--2--2--1
           1--2--3--4--5--5--5

```

Next step: connect the species:

```
     9--8--6--5--4--4--4--4--4
        |  |  |  |  |
        1--2--2--2--1
           |  |  |  |
           1--2--3--4--5--5--5

```

Next step: summarize species:

 * One species possible: keep solid line
 * More species possible: use dotted line

```
           +--- speciation initiation
           |        +--- speciation completion
           |        |
           v        v
     9--9--9..9..9..9--4--4--4
                     \-5--5--5
```

Next step: summarize edges (the number above the edge denotes its length):

```
       2   3      2
     9---9...9--4---4
              \
               \  2
                5---5
```

*/
BOOST_AUTO_TEST_CASE(test_results_example_complete_speciation)
{
  //+--+--+--+--+--+--+--+--+--+--+
  //|G |t1|t2|t3|t4|t5|t6|t7|t8|t9|
  //+--+--+--+--+--+--+--+--+--+--+
  //|00| 9| 8| 6| 5| 4| 4| 4| 4| 4|
  //|01|  | 1| 2| 2| 2| 1|  |  |  |
  //|11|  |  | 1| 2| 3| 4| 5| 5| 5|
  //|10|  |  |  |  |  |  |  |  |  |
  //+--+--+--+--+--+--+--+--+--+--+
  const individual i00(dna(""), sil(2,0b00));
  const individual i01(dna(""), sil(2,0b01));
  const individual i11(dna(""), sil(2,0b11));

  std::vector<population> populations{
    population_factory().create(
      9, i00,
      0, i01,
      0, i11
    ),
    population_factory().create(
      8, i00,
      1, i01,
      0, i11
    ),
    population_factory().create(
      6, i00,
      2, i01,
      1, i11
    ),
    population_factory().create(
      5, i00,
      2, i01,
      2, i11
    ),
    population_factory().create(
      4, i00,
      2, i01,
      3, i11
    ),
    population_factory().create(
      4, i00,
      1, i01,
      4, i11
    ),
    population_factory().create(
      4, i00,
      0, i01,
      5, i11
    ),
    population_factory().create(
      4, i00,
      0, i01,
      5, i11
    ),
    population_factory().create(
      4, i00,
      0, i01,
      5, i11
    )
  };
  assert(populations.size() == 9);
  const int n_populations{static_cast<int>(populations.size())};
  const int max_genetic_distance{1};
  results r(max_genetic_distance);
  for (int t=0; t!=n_populations; ++t)
  {
    assert(t >= 0 && t < static_cast<int>(populations.size()));
    r.add_measurement(t, populations[t]);
  }
  {
    const std::string filename_base{"test_results_example_complete_speciation_1"};
    const std::string filename_dot{filename_base + ".dot"};
    const std::string filename_svg{filename_base + ".svg"};
    const std::string filename_png{filename_base + ".png"};
    std::ofstream f(filename_dot);
    f << r.get_sil_frequency_phylogeny();
    BOOST_CHECK(is_regular_file(filename_dot));
    convert_dot_to_svg(filename_dot, filename_svg);
    convert_svg_to_png(filename_svg, filename_png);
    //const std::string cmd{"display " + filename_png};
    //std::system(cmd.c_str());
  }
  r.summarize_genotypes();
  {
    const std::string filename_base{"test_results_example_complete_speciation_2"};
    const std::string filename_dot{filename_base + ".dot"};
    const std::string filename_svg{filename_base + ".svg"};
    const std::string filename_png{filename_base + ".png"};
    std::ofstream f(filename_dot);
    f << r.get_sil_frequency_phylogeny();
    BOOST_CHECK(is_regular_file(filename_dot));
    convert_dot_to_svg(filename_dot, filename_svg);
    convert_svg_to_png(filename_svg, filename_png);
    //const std::string cmd{"display " + filename_png};
    //std::system(cmd.c_str());
  }
}

/*


This also allows for unsuccessfull speciation-initiations:

```
+--+--+--+--+--+--+--+--+--+--+
|G |t1|t2|t3|t4|t5|t6|t7|t8|t9|
+--+--+--+--+--+--+--+--+--+--+
|00| 9| 8| 6| 5| 4| 4| 5| 5| 4|
|01|  | 1| 2| 2| 2| 1| 2| 4| 5|
|11|  |  | 1| 2| 3| 4| 2|  |  |
|10|  |  |  |  |  |  |  |  |  |
+--+--+--+--+--+--+--+--+--+--+
```

Next step: create a graph from this:

```
     9--8--6--5--4--4--5--5--4
        1--2--2--2--1--2--4--5
           1--2--3--4--2

```

Next step: connect the species:

```
     9--8--6--5--4--4--5--5--4
        |  |  |  |  |  |  |  |
        1--2--2--2--1--2--4--5
           |  |  |  |  |
           1--2--3--4--2

```

Next step: summarize species:

 * One species possible: keep solid line
 * More species possible: use dotted line

```
           +--- speciation initiation
           |           +--- end of speciation-initiation
           |           |
           v           v
     9--9--9..9..9..9..9--9--9
```

Next step: summarize edges (the number above the edge denotes its length):

```
       2   4   2
     9---9...9---9
```

*/
BOOST_AUTO_TEST_CASE(test_results_example_unsuccessfull_speciation)
{

}



/*

There is a problem case, I do not think is a problem:


```
+---+--+--+--+--+--+--+--+--+--+
| G |t1|t2|t3|t4|t5|t6|t7|t8|t9|
+---+--+--+--+--+--+--+--+--+--+
|000|  |  |  | 2| 2| 2| 2|  |  |
|001|  | 3| 3| 2| 2| 2| 2| 3|  |
|011| 9| 3| 3|  |  |  | 1| 3| 9|
|010|  | 3| 3| 3| 3| 3| 2| 3|  |
|110|  |  |  | 2| 2| 2| 2|  |  |
+---+--+--+--+--+--+--+--+--+--+
```

Next step: create a graph from this:

```
            2--2--2--2
      3--3--2--2--2--2--3
   9--3--3           1--3--9
      3--3--3--3--3--2--3
            2--2--2--2

```

Next step: connect the species:

```
            2--2--2--2
            |  |  |  |
      3--3--2--2--2--2--3
      |  |           |  |
   9--3--3           1--3--9
      |  |           |  |
      3--3--3--3--3--2--3
            |  |  |  |
            2--2--2--2

```

Next step: summarize species:

 * One species possible: keep solid line
 * More species possible: use dotted line

```
      +--- speciation initiation
      |  +--- end of speciation-initiation
      |  |
      v  v
   9--9..9--4--4--4--9--9--9
          \         /
           \       /
            5--5--5

```

Next step: smash loops, use an equals (`=`) line here:

```
      +--- speciation initiation
      |              +--- end of speciation-initiation
      |              |
      v              v
   9--9..9==9==9==9==9--9--9

```

An equals (`=`) line denotes: there were two species, that could reform the
missing link again. These occurrances should be rare for more loci! I
intend to treat these lineages as incipient species, as they could
not keep a good species established.

Next step: summarize edges (the number above the edge denotes its length):

```
       2   1   4   2
     9---9...9===9---9
```
*/
BOOST_AUTO_TEST_CASE(test_results_example_problem_case)
{

}
