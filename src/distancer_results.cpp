#include "distancer_results.h"
#include <iostream>
#include <sstream>
#include "add_bundled_vertex.h"
#include "distancer_sil.h"
#include "save_bundled_vertices_graph_to_dot.h"
#include "distancer_helper.h"

results::results()
  : m_sil_frequency_phylogeny{}
{

}

void results::add_measurement(
  const int t ,
  const population& any_population,
  const int /* max_genetic_distance */
) noexcept
{
  if (t < 0)
  {
    std::stringstream msg;
    msg << __func__ << ": generation 't' cannot be "
      << "negative, value supplied is " << t
    ;
    throw std::invalid_argument(msg.str());
  }
  //Tally SILs
  const auto m = tally_sils(any_population);

  //Add vertex
  for (const auto p: m)
  {
    add_bundled_vertex(
      sil_frequency_vertex(
        p.second,
        p.first
      ),
      m_sil_frequency_phylogeny
    );
  }
  //Connect species vertex
}

std::ostream& operator<<(std::ostream& os, const results& r) noexcept
{
  const auto g = r.get_sil_frequency_phylogeny();
  boost::write_graphviz(os, g,
    sil_frequency_vertex_writer<sil_frequency_phylogeny>(g)
  );
  //?Newline is required by R's read.table function
  return os;
}
