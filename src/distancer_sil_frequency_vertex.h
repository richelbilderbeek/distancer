#ifndef DISTANCER_RESULTS_VERTEX_H
#define DISTANCER_RESULTS_VERTEX_H

#include <map>
#include <boost/graph/graph_traits.hpp>
#include "distancer_sil.h"

class sil_frequency_vertex
{
public:
  sil_frequency_vertex();

  explicit sil_frequency_vertex(
    const std::map<sil,int>& sil_frequencies,
    const int time
  );

  std::map<sil,int> get_sil_frequencies() const noexcept { return m_sil_frequencies; }

  ///The timepoint
  int get_time() const noexcept { return m_time; }

private:
  std::map<sil,int> m_sil_frequencies;
  //int m_frequency;
  //sil m_sil;
  int m_time;
};

/*
template <typename graph>
std::map<sil,int> get_sil_frequencies(
  const typename boost::graph_traits<graph>::vertex_descriptor& vd,
  const graph& g
) noexcept
{
  return g[vd].get_sil_frequencies();
}

template <typename graph>
int get_vertex_time(
  const typename boost::graph_traits<graph>::vertex_descriptor& vd,
  const graph& g
) noexcept
{
  return g[vd].get_time();
}
*/

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
  ) const noexcept
  {

    std::stringstream str;
    const auto fs = m_g[vd].get_sil_frequencies();
    for (const auto p: fs) {
      str << p.first << "(" << p.second << "),";
    }
    std::string fss = str.str();
    if (!fss.empty()) fss.pop_back(); //Get rid of trailing comma

    out
      << "[label=\""
      << m_g[vd].get_time()
      << ": "
      << fss
      << "\"]"
    ;
  }
private:
  graph m_g;
};

#endif // DISTANCER_RESULTS_VERTEX_H
