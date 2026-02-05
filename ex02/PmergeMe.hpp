#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <deque>
#include <vector>

class	PmergeMe {
public:
	PmergeMe() = delete;
	PmergeMe(const PmergeMe&) = delete;
	virtual PmergeMe& operator =(const PmergeMe&) = delete;
	virtual ~PmergeMe() = delete;
	// internal state's for suckas

	static void	sort(std::vector<int>&);
	static void	sort(std::deque<int>&);
	static std::size_t	jacobsthalSequence(std::size_t n);
private:
protected:
};

#endif // PMERGEME_HPP
