#ifndef DISTANCER_RESULTS_VERTEX_H
#define DISTANCER_RESULTS_VERTEX_H

#include <boost/graph/graph_traits.hpp>
#include "distancer_sil.h"
#include "distancer_pin.h"

class results_vertex
{
public:
  results_vertex(
    const int frequency = 0,
    const dna& any_pin = dna(),
    const sil& any_sil = sil()
  );

  ///The number of individuals with this SIL
  int get_frequency() const noexcept { return m_frequency; }

  ///The Phylogny Inference Nucleotides
  const dna& get_pin() const noexcept { return m_pin; }

  ///The Species Identification Loci
  const sil& get_sil() const noexcept { return m_sil; }
private:
  int m_frequency;
  dna m_pin;
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
pin get_vertex_pin(
  const typename boost::graph_traits<graph>::vertex_descriptor& vd,
  const graph& g
) noexcept
{
  return g[vd].get_pin();
}

template <typename graph>
sil get_vertex_sil(
  const typename boost::graph_traits<graph>::vertex_descriptor& vd,
  const graph& g
) noexcept
{
  return g[vd].get_sil();
}

#endif // DISTANCER_RESULTS_VERTEX_H
