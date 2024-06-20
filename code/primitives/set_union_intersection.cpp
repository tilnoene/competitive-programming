// Template pra fazer união e intercessão de sets de forma fácil
// Usar + para uniao e * para intercessão
// Source: https://stackoverflow.com/questions/13448064/how-to-find-the-intersection-of-two-stl-sets

template <class T, class CMP = std::less<T>, class ALLOC = std::allocator<T> >
std::set<T, CMP, ALLOC> operator * (
  const std::set<T, CMP, ALLOC> &s1, const std::set<T, CMP, ALLOC> &s2)
{
  std::set<T, CMP, ALLOC> s;
  std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
    std::inserter(s, s.begin()));
  return s;
}

template <class T, class CMP = std::less<T>, class ALLOC = std::allocator<T> >
std::set<T, CMP, ALLOC> operator + (
  const std::set<T, CMP, ALLOC> &s1, const std::set<T, CMP, ALLOC> &s2)
{
  std::set<T, CMP, ALLOC> s;
  std::set_union(s1.begin(), s1.end(), s2.begin(), s2.end(),
    std::inserter(s, s.begin()));
  return s;
}