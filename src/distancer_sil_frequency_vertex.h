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

  #ifndef NDEBUG
  int get_id() const noexcept { return m_id; }
  #endif // NDEBUG

  ///The SIL frequencies
  std::map<sil,int> get_sil_frequencies() const noexcept { return m_sil_frequencies; }

  ///The timepoint
  int get_time() const noexcept { return m_time; }

private:
  #ifndef NDEBUG
  int m_id; ///Unique ID
  static int s_m_next_id;
  #endif // NDEBUG

  ///The SIL frequencies
  std::map<sil,int> m_sil_frequencies;

  ///The timestep
  int m_time;

  friend void move_sil_frequencies(sil_frequency_vertex& from, sil_frequency_vertex& to);
};

///Get the SIL frequencies as a std::string
std::string get_sil_frequencies_str(const sil_frequency_vertex& v) noexcept;

///Move all SIL frequences from 'from' to 'to'
void move_sil_frequencies(sil_frequency_vertex& from, sil_frequency_vertex& to);

std::ostream& operator<<(std::ostream& os, const sil_frequency_vertex& v) noexcept;

#endif // DISTANCER_RESULTS_VERTEX_H
