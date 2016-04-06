#ifndef DISTANCER_sil_frequency_vertex_writer_H
#define DISTANCER_sil_frequency_vertex_writer_H

#include <cassert>
#include <sstream>
#include <ostream>
//#include "graphviz_encode.h"
//#include "is_graphviz_friendly.h"

template <
  typename graph
>
class sil_frequency_vertex_writer {
public:
  sil_frequency_vertex_writer(
    graph g,
    const int max_genetic_distance
  ) : m_g{g},
      m_max_genetic_distance{max_genetic_distance}
  {
    assert(m_max_genetic_distance > 0);
  }
  template <class vertex_descriptor>
  void operator()(
    std::ostream& out,
    const vertex_descriptor& vd
  ) const noexcept
  {
    //SIL frequencies
    std::stringstream str;
    const auto fs = m_g[vd].get_sil_frequencies();
    for (const auto p: fs) {
      str << p.first << "(" << p.second << "),";
    }
    std::string fss = str.str();
    if (!fss.empty()) fss.pop_back(); //Get rid of trailing comma

    //Style string
    out
      << "["
      << "label=\""
      #ifndef NDEBUG
      << m_g[vd].get_id() << ": "
      #endif
      << m_g[vd].get_time()
      << ": "
      << fss
      << "\""
    ;
    if (m_g[vd].count_n_possible_species(m_max_genetic_distance) > 1 )
    {
      out << " style=dotted";
    }
    out
      << "]"
    ;
  }
private:
  graph m_g;
  int m_max_genetic_distance;
};


#endif // DISTANCER_sil_frequency_vertex_writer_H
