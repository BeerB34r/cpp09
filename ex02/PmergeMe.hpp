#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <deque>
#include <vector>

class	PmergeMe {
public:
	PmergeMe();
	PmergeMe(const PmergeMe&);
	virtual PmergeMe& operator =(const PmergeMe&) = 0;
	virtual ~PmergeMe() = 0;

	void	sort(std::vector<int>&);
	void	sort(std::deque<int>&);
private:
protected:
};

#endif // PMERGEME_HPP
