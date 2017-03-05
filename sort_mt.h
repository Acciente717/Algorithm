/*
#########################
###     sort_mt.h     ###
###      By Acc.      ###
###      Ver 1.0      ###
###    2017-03-05     ###
#########################

*** Caution ***
Sorting a container with random iterator may cause crush when using VisualStudio in debug mode.

This function works like "sort" in <algorithm>.
It creates multiple threads when running.
You can indicate the thread number by define the parameter "thread_power".
"thread_power" means the function will run in 2 ^ x threads when possible.
The default value is 2, which means it will run in 2 ^ 2 == 4 threads when possible.

The function prototype is:
void sort_mt(RanIt begin_, RanIt end_, Pred cmp, int thread_power);
"begin_" and "end_" are the pointers or iterators indicating the range [begin_, end_).
"cmp" is the customized function used to compare the elements. (same as "sort", and it can be omitted.)
"thread_power": see above.

*/

#include <thread>

template<class RanIt, class Pred>
static void __sort_mt_kernel_customize(RanIt begin_, RanIt end_, Pred cmp, int thread_power);

template<class RanIt, class Pred>
class __sort_mt_customize_thread_handler
{
public:
	RanIt begin_, end_;
	Pred cmp_;
	int thread_power_;
	__sort_mt_customize_thread_handler(RanIt _begin_, RanIt _end_, Pred _cmp_, int _thread_power_) \
		: begin_(_begin_), end_(_end_), cmp_(_cmp_), thread_power_(_thread_power_) {};
	void operator()()
	{
		__sort_mt_kernel_customize(begin_, end_, cmp_, thread_power_);
	}
};

template<class RanIt, class Pred>
static void __sort_mt_kernel_default(RanIt begin_, RanIt end_, Pred cmp, int thread_power);

template<class RanIt, class Pred>
class __sort_mt_default_thread_handler
{
public:
	RanIt begin_, end_;
	Pred cmp_;
	int thread_power_;
	__sort_mt_default_thread_handler(RanIt _begin_, RanIt _end_, Pred _cmp_, int _thread_power_) \
		: begin_(_begin_), end_(_end_), cmp_(_cmp_), thread_power_(_thread_power_) {};
	void operator()()
	{
		__sort_mt_kernel_default(begin_, end_, cmp_, thread_power_);
	}
};


class __sort_mt_default_cmp
{
public:
	template<class Type>
	bool operator()(Type a, Type b)
	{
		return a < b;
	}
};

template<class Type>
inline static void __sort_mt_swap(Type &a, Type &b)
{
	Type temp;
	temp = a;
	a = b;
	b = temp;
}

template<class RanIt, class Pred>
static void __sort_mt_kernel_customize(RanIt begin_, RanIt end_, Pred cmp, int thread_power)
{
	if (end_ - begin_ > 2)
	{
		RanIt p = begin_, smallP = begin_, largeP = end_ - 1, temp;
		for (;;)
		{
			for (; largeP != smallP && !(*cmp)(*largeP, *p); --largeP);
			if (largeP == smallP)
				break;
			__sort_mt_swap(*p, *largeP);
			p = largeP;
			for (; largeP != smallP && !(*cmp)(*p, *smallP); ++smallP);
			if (largeP == smallP)
				break;
			__sort_mt_swap(*p, *smallP);
			p = smallP;
		}
		if (thread_power) // going to split to two threads
		{
			std::thread left_thread;
			std::thread right_thread;
			if (p > begin_ + 1)
			{
				__sort_mt_customize_thread_handler<RanIt, Pred> left(begin_, p, cmp, thread_power - 1);
				left_thread = std::thread(left);
			}
			if (end_ > p + 2)
			{
				__sort_mt_customize_thread_handler<RanIt, Pred> right(p + 1, end_, cmp, thread_power - 1);
				right_thread = std::thread(right);
			}
			if (p > begin_ + 1)
				left_thread.join();
			if (end_ > p + 2)
				right_thread.join();
		}
		else // not going to split any thread
		{
			if (p > begin_ + 1)
				__sort_mt_kernel_customize(begin_, p, cmp, thread_power);
			if (end_ > p + 2)
				__sort_mt_kernel_customize(p + 1, end_, cmp, thread_power);
		}
	}
	else if (end_ - begin_ > 1)
	{
		if ((*cmp)(*begin_, *(end_ - 1)))
			return;
		else if ((*cmp)(*(end_ - 1), *begin_))
			__sort_mt_swap(*begin_, *(end_ - 1));
	}
}

template<class RanIt, class Pred>
static void __sort_mt_kernel_default(RanIt begin_, RanIt end_, Pred cmp, int thread_power)
{
	if (end_ - begin_ > 2)
	{
		RanIt p = begin_, smallP = begin_, largeP = end_ - 1, temp;
		for (;;)
		{
			for (; largeP != smallP && !cmp(*largeP, *p); --largeP);
			if (largeP == smallP)
				break;
			__sort_mt_swap(*p, *largeP);
			p = largeP;
			for (; largeP != smallP && !cmp(*p, *smallP); ++smallP);
			if (largeP == smallP)
				break;
			__sort_mt_swap(*p, *smallP);
			p = smallP;
		}
		if (thread_power) // going to split to two threads
		{
			std::thread left_thread;
			std::thread right_thread;
			if (p > begin_ + 1)
			{
				__sort_mt_default_thread_handler<RanIt, Pred> left(begin_, p, cmp, thread_power - 1);
				left_thread = std::thread(left);
			}
			if (end_ > p + 2)
			{
				__sort_mt_default_thread_handler<RanIt, Pred> right(p + 1, end_, cmp, thread_power - 1);
				right_thread = std::thread(right);
			}
			if (p > begin_ + 1)
				left_thread.join();
			if (end_ > p + 2)
				right_thread.join();
		}
		else // not going to split any thread
		{
			if (p > begin_ + 1)
				__sort_mt_kernel_default(begin_, p, cmp, thread_power);
			if (end_ > p + 2)
				__sort_mt_kernel_default(p + 1, end_, cmp, thread_power);
		}
	}
	else if (end_ - begin_ > 1)
	{
		if (cmp(*begin_, *(end_ - 1)))
			return;
		else if (cmp(*(end_ - 1), *begin_))
			__sort_mt_swap(*begin_, *(end_ - 1));
	}
}

template<class RanIt, class Pred>
void sort_mt(RanIt begin_, RanIt end_, Pred cmp)
{
	__sort_mt_kernel_customize(begin_, end_, cmp, 2);
}

template<class RanIt>
void sort_mt(RanIt begin_, RanIt end_)
{
	__sort_mt_kernel_default(begin_, end_, __sort_mt_default_cmp(), 2);
}

template<class RanIt, class Pred>
void sort_mt(RanIt begin_, RanIt end_, Pred cmp, int thread_power)
{
	thread_power = thread_power < 0 ? 0 : thread_power;
	__sort_mt_kernel_customize(begin_, end_, cmp, thread_power);
}

template<class RanIt>
void sort_mt(RanIt begin_, RanIt end_, int thread_power)
{
	thread_power = thread_power < 0 ? 0 : thread_power;
	__sort_mt_kernel_default(begin_, end_, __sort_mt_default_cmp(), thread_power);
}