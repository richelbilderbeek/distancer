#ifndef DISTANCER_RESULTS_VERTEX_H
#define DISTANCER_RESULTS_VERTEX_H

#include <boost/graph/graph_traits.hpp>
#include "distancer_sil.h"

class sil_frequency_vertex
{
public:
  sil_frequency_vertex(
    const int frequency = 0,
    const sil& any_sil = sil()
  );

  ///The number of individuals with this SIL
  int get_frequency() const noexcept { return m_frequency; }

  ///The Species Identification Loci
  const sil& get_sil() const noexcept { return m_sil; }
private:
  int m_frequency;
  sil m_sil;
};

template <typename graph>
int get_vertex_frequency(
  const typename boost::graph_traits<graph>::vertex_descriptor& vd,
  const graph& g
) noexcept
{
  return g[vd].get_frequency();
}

template <typename graph>
sil get_vertex_sil(
  const typename boost::graph_traits<graph>::vertex_descriptor& vd,
  const graph& g
) noexcept
{
  return g[vd].get_sil();
}

#include <ostream>
#include "graphviz_encode.h"
#include "is_graphviz_friendly.h"

template <
  typename graph
>
class sil_frequency_vertex_writer {
public:
  sil_frequency_vertex_writer(
    graph g
  ) : m_g{g}
  {

  }
  template <class vertex_descriptor>
  void operator()(
    std::ostream& out,
    const vertex_descriptor& vd
  ) const noexcept {
    out
      << "[label=\""
      << m_g[vd].get_sil()
      << ", " << m_g[vd].get_frequency()
      << "\"]"
    ;
  }
private:
  graph m_g;
};

#endif // DISTANCER_RESULTS_VERTEX_H
