
##  According to “On Following Rules”, what rules should we never break?
    Follow every rule you don't understand.
    Only break rules you fully understand and have good reason to break.
	
## According to “On Following Rules”, how should we deal with a rule we do not understand?
    Follow it

## According to “On Following Rules”, when can we break a rule?
    When you understand it
## Give an example of a rule, as the term is used in “On Following Rules”.
    Goto considered harmful.
## Give an example of a rule that you might correctly break, according to the standards in “On Following Rules”, and explain circumstances in which you would break it.
    Goto may be used when performace is extremly important or low level coding. For example I am writing a game on a old console. I may have to use GOTO
## What is an expression?
    Something that has a value
## True or false? When a type conversion is applied to a variable, it may alter the value of the variable.
   false because data is only translated to things that have more detail, int to float, not float to int. (Actually that may be considered loosing info)
## What is an Lvalue? What is an Rvalue?
    rvalue: something that lives in an expression only
    lvalue: something that outlives an expression.

##    Classify expressions in some C++ code as Lvalue or Rvalue.
    Example. Consider the following C++ code.

              vector<int> data(10);
              const int m = 3;
              data[0] = m;
              data[m] = 37+data[0];

    Classify each of the following as Lvalue or Rvalue.
        data: lvalue
        data[0]: lvalue
        m: lvalue
        data[m]: lvalue
        37: rvalue
        37+data[0]: rvalue

## Which C++ expressions are simultaneously both Lvalues and Rvalues? Which C++ expressions are neither Lvalues nor Rvalues?
   NONE! either lvalue or rvalue not both
## Name and briefly explain each of the four C++ parameter-passing methods we discussed.
by value:
```void foo(bar bars);```
by refrence:
```void foo(bar& bars);```
by refrence to const:
```void foo(const bar& bars);```
by rvalue refrence:
```void foo(bar&& bars);```

## Under normal circumstances, which parameter-passing method is used to pass an int?
```void foo(int bar);```
## Under normal circumstances, which parameter-passing method is used to pass a vector<int>?
```void foo(const std::vector<int>& bar);```
## Under normal circumstances, which parameter-passing method is used to pass an iterator?
    ??
## What is a special circumstance in which we would use pass by value to pass something of a type that we would not normally pass by value?
   when I want a copy that I can change
## When do we return by reference / reference-to-const?
   WHen there is a large variable that takes a long time to copy
## What does overloading mean?
   1 name can call 2 different methods
## What do we mean by the arity of an operator?
   Number of arguments that an operator takes
## In C++, we can implement an overloaded operator using either a global function or a member function. How does this choice affect the parameters the function takes?
    member function does not allow type conversion
    Global allows type conversion
## We generally want to implement an operator using a member function, when we have no good reason not it. Give two good reasons not to, which may apply to some operators.
    1. We can not modify the object
    2. We need type conversion

## List the Big Five.
If you have to write the Deconstructor copy ctor move ctor =copy =move write all 5
## Give an example of a member function that a C++ compiler may automatically write for you.
operator=
## What is a default constructor?
constructor with no arguments
## What is an assignment operator?
operator=
## When we talk about a copy constructor or a copy assignment operator, what do we mean by “copy”?
data in class is copied
## When we talk about a move constructor or a move assignment operator, what do we mean by “move”?
data is never moved, owenrship is transferred

## Explain the differences between a copy constructor and a move constructor: how they take their parameters, and what they (probably) do.
	move: foo(foo&& bar);
	copy foo(foo& bar);

## In what circumstances does C++ automatically write a class’s default constructor?
    When everything has a ctor already
## Your instructor refers to certain functions as “invisible”. What does he mean?
    The fctn is never explicitly called
## Suppose we want a C++ class to have no copy operations. How can we eliminate these operations?
    foo(foo& bar)=delete;
## State the Rule of Five.
If you have to write the Deconstructor copy ctor move ctor =copy =move write all 5
## What is an invariant
SOmething that is assumed to always be true
## Explain preconditions and postconditions. What do we use these for?
## What is an operation contract? How is it like a real-world contract?
If {precondition} then {post condition

## What is a class invariant?
something is true in a class
## Finish the following.
A class invariant is a precondition of every public member function, except ctors
A class invariant is a postcondition of every public member function, except dctors
## Given a description of a function, write reasonable pre- and postconditions for the function.
    Given a description of a class, write reasonable class invariants.
    Your instructor says that talking about “the constructor” (as opposed to “a constructor”) usually indicates that there is a misunderstanding. What is this misunderstanding?
    Your instructor says that the first goal, when writing code, should be to get it to compile. Why is this? What important advantage do we lose when we work on code for an extended time without being able to compile it?
    Some people are in the habit of writing a whole bunch of code, saying, “I’m done,” and then trying to compile it for the first time. Your instructor replies, “No, you’re not done; you just started.” Explain.
    What is wrong with writing (say) a bracket operator for an array class, that takes an int parameter? What would be a better choice for the parameter type?
    What does the destructor of a pointer do?
    What does it mean to release a resource? Give an example of a specific resource, and indicate exactly what it means to release this resource.
    What do we mean by ownership?
    RAII is misleading, but standard, terminology. What does it really mean? (I am not asking what it stands for.)
    What kinds of troubles does RAII help to prevent?
    Give an example of a C++ Standard Library class or class template that uses RAII.
    Explain the use of the C++ explicit keyword.
    Class IntArray allocates by doing “new value_type[size]”. It could also have done “new int[size]”, but your instructor says the former is better. Why?
    What are circular references? How would they affect they way we make use of ownership?
    What do we mean by a generic container?
    What can we do with random-access data, that we cannot do with sequential-access data?
    Give an example of some sequential-access data. Give an example of some random-access data.
    What is a first-class type?
    What is an iterator?
    An iterator refers to an item in a container—or it acts as if it does. Explain.
    An iterator references an item in a container. Does the iterator own that item?
    How do we specify a range of data using two iterators? (The iterators each refer to something. What somethings do they each refer to? Be specific.)
    Explain foward, bidirectional, and random-access iterators. How do they differ?
    Give an example of a range-based for-loop.
    What is the connection between a range-based for-loop and the begin and end member functions that most container classes have?
    For each of the following STL algorithms, explain what it does and how it is called: std::copy, std::equal, std::sort, std::fill.
    State the Rule of Zero.
    What do we mean by an error condition?
    True or false: When an error condition occurs in a function, the function must inform the caller.
    There are three—and only three—ways to deal with the possibility of an error condition in a function. What are they? Hint: “throwing an exception” is not one of them.
    What does DRY stand for? What does it mean?
    What does it mean when two modules are tightly coupled? Is this a good thing or a bad thing?
    What does it mean for a module to be cohesive? Is this a good thing or a bad thing?
    What is an exception?
    What happens if a C++ exception is thrown, but it is never caught?
    What C++ keyword is used when throwing an exception?
    What C++ syntax do we use to catch every exception, and then rethrow the same exception when we have done what we need to? Be precise & detailed.
    For each statement below, indicate whether you instructor says it is true or false. If true, then explain why he says it is true.
        In C++, constructors should not throw.
        In C++, destructors should not throw.
    Some people dislike exceptions, because using them means that programmers are required to do lots of work. Let us take it as given that (1) exceptions do make lots of work for programmers, and (2) we do not want programmers to be overworked. Nonetheless, your instructor claims that this is a bad reason to dislike exceptions. Why does he say that?
    What do we mean by abstraction?
    In this class, what do we mean by a client of a module?
    What is a Linked List?
    What two pieces of data does a Linked List node hold?
    How do we mark the end of a Linked List?
    An empty Linked List has no nodes. How do we represent an empty Linked List.
    A Linked List holds essentially the same kind of data as an array. Why, then, would we ever want to use a Linked List? We could simply use (smart) arrays for everything, right?
    What is the difference between a Singly Linked List and a Doubly Linked List?
    What does it mean to be recursive?
    What happens if a recursive function never reaches its base case?
    Explain direct vs. indirect recursion.
    Briefly explain how the Binary Search algorithm works.
    In the context of Binary Search, what is a pivot?
    Your instructor says that if we search for an item in a list using operator<, then we should also determine whether we found it using operator<. Why?
    Explain C++ equality vs. equivalence.
    What do std::distance and std::advance do? Explain how using them can be a better choice than doing pointer-arithmetic-style operations on iterators using operators.
    What do we mean by workhorse and wrapper functions?
    What is the call stack? What is a stack frame?
    When is a push done on the call stack? When is a pop done on the call stack? What do these two operations do?
    What is the return address of a function call? Where is it stored?
    What do we mean by an invocation of a function?
    What is the recursion depth of a function call? Why is recursion depth important?
    What are two typical sources of trouble when we use recursion?
    What problems can be caused by excessive recursion depth?
    Given a list of size to search in, at most how many list items does Binary Search need to examine (roughly)?
    Briefly explain how the Sequential Search algorithm works.
    Why is Sequential Search sometimes preferable to Binary Search?
    A quote mentioned during the lecture: “As machines become more powerful, the efficiency of algorithms grows more important, not less.” How can this possibly be true?
    Binary Search requires a sorted list, and it is only efficient if the list is random-access. Sequential Search, on the other hand, works for just about any dataset. Why, then, do we generally prefer Binary Search?
    What is a tail call?
    What does TCO stand for? What does it mean?
    What is tail recursion?
    Why do we like tail recursion? Hint: there might be some irony here.
    What is backtracking?
    What does it mean to say that an algorithm is efficient? This term has both a general and a specific meaning; explain both.
    We are interested in algorithms that use few resources. In this context, what is generally the most important resource?
    What does the term basic operation mean?
    When we analyze an algorithm, we can choose anything we want for our basic operations. What are our usual basic operations, in this class?
    What does it mean for an algorithm (or technique or strategy or …) to be scalable?
    Convert between big- notation and words when describing time efficiency of an algorithm.
    Examples.
        Suppose the order (time efficiency) of some algorithm is . Express this in words.
        Suppose some algorithm is log-linear time. Express this using big- notation.
    Compare efficiency categories, indicating which is faster.
    Examples
        Which is faster, quadratic time or logarithmic time?
    Algorithms faster than linear time are rare. This is because there is a specific thing that such an algorithm cannot do. What is it?
    In our list of efficiency categories, there were two categories that were faster than linear time. Name these two categories.
    Roughly speaking, how slow can an algorithm be and still be considered scalable? Answer using our standard terminology for efficiency categories.
    Briefly explain our “Rule of Thumb” for finding the order of an algorithm involving nested loops.
    In computing, what do we mean by sorting?
    What is a comparison sort?
    In this class, we use the term general-purpose comparison sort. What does this mean?
    What does it mean for an algorithm to be in-place?
    What does it mean for a sorting algorithm to be stable?
    What is the order of Bubble Sort?
    When is Bubble Sort used in practice?
    Explain how Insertion Sort works.
    What is the order of Insertion Sort?
    Is Insertion Sort in-place?
    Is Insertion Sort stable?
    When is Insertion Sort used in practice?
    Bubble Sort and Insertion Sort are both too slow for general-purpose use. Their time efficiency has the same order. And yet, in practice, Insertion Sort does see some use, while Bubble Sort largely does not. Explain.
    According to “On Following Rules”, what rules should we never break?
    According to “On Following Rules”, how should we deal with a rule we do not understand?
    According to “On Following Rules”, when can we break a rule?
    Give an example of a rule, as the term is used in “On Following Rules”.
    Give an example of a rule that you might correctly break, according to the standards in “On Following Rules”, and explain circumstances in which you would break it.
    What is an expression?
    True or false? When a type conversion is applied to a variable, it may alter the value of the variable.
    What is an Lvalue? What is an Rvalue?
    Classify expressions in some C++ code as Lvalue or Rvalue.
    Example. Consider the following C++ code.

              vector<int> data(10);
              const int m = 3;
              data[0] = m;
              data[m] = 37+data[0];

    Classify each of the following as Lvalue or Rvalue.
        data
        data[0]
        m
        data[m]
        37
        37+data[0]
    Which C++ expressions are simultaneously both Lvalues and Rvalues? Which C++ expressions are neither Lvalues nor Rvalues?
    Name and briefly explain each of the four C++ parameter-passing methods we discussed.
    Under normal circumstances, which parameter-passing method is used to pass an int?
    Under normal circumstances, which parameter-passing method is used to pass a vector<int>?
    Under normal circumstances, which parameter-passing method is used to pass an iterator?
    What is a special circumstance in which we would use pass by value to pass something of a type that we would not normally pass by value?
    When do we return by reference / reference-to-const?
    What does overloading mean?
    What do we mean by the arity of an operator?
    In C++, we can implement an overloaded operator using either a global function or a member function. How does this choice affect the parameters the function takes?
    We generally want to implement an operator using a member function, when we have no good reason not it. Give two good reasons not to, which may apply to some operators.
    List the Big Five.
    Give an example of a member function that a C++ compiler may automatically write for you.
    What is a default constructor?
    What is an assignment operator?
    When we talk about a copy constructor or a copy assignment operator, what do we mean by “copy”?
    When we talk about a move constructor or a move assignment operator, what do we mean by “move”?
    Explain the differences between a copy constructor and a move constructor: how they take their parameters, and what they (probably) do.
    In what circumstances does C++ automatically write a class’s default constructor?
    Your instructor refers to certain functions as “invisible”. What does he mean?
    Suppose we want a C++ class to have no copy operations. How can we eliminate these operations?
    State the Rule of Five.
    What is an invariant?
    Explain preconditions and postconditions. What do we use these for?
    What is an operation contract? How is it like a real-world contract?
    What is a class invariant?
    Finish the following.
        A class invariant is a precondition of every public member function, except …
        A class invariant is a postcondition of every public member function, except …
    Given a description of a function, write reasonable pre- and postconditions for the function.
    Given a description of a class, write reasonable class invariants.
    Your instructor says that talking about “the constructor” (as opposed to “a constructor”) usually indicates that there is a misunderstanding. What is this misunderstanding?
    Your instructor says that the first goal, when writing code, should be to get it to compile. Why is this? What important advantage do we lose when we work on code for an extended time without being able to compile it?
    Some people are in the habit of writing a whole bunch of code, saying, “I’m done,” and then trying to compile it for the first time. Your instructor replies, “No, you’re not done; you just started.” Explain.
    What is wrong with writing (say) a bracket operator for an array class, that takes an int parameter? What would be a better choice for the parameter type?
    What does the destructor of a pointer do?
    What does it mean to release a resource? Give an example of a specific resource, and indicate exactly what it means to release this resource.
    What do we mean by ownership?
    RAII is misleading, but standard, terminology. What does it really mean? (I am not asking what it stands for.)
    What kinds of troubles does RAII help to prevent?
    Give an example of a C++ Standard Library class or class template that uses RAII.
    Explain the use of the C++ explicit keyword.
    Class IntArray allocates by doing “new value_type[size]”. It could also have done “new int[size]”, but your instructor says the former is better. Why?
    What are circular references? How would they affect they way we make use of ownership?
    What do we mean by a generic container?
    What can we do with random-access data, that we cannot do with sequential-access data?
    Give an example of some sequential-access data. Give an example of some random-access data.
    What is a first-class type?
    What is an iterator?
    An iterator refers to an item in a container—or it acts as if it does. Explain.
    An iterator references an item in a container. Does the iterator own that item?
    How do we specify a range of data using two iterators? (The iterators each refer to something. What somethings do they each refer to? Be specific.)
    Explain foward, bidirectional, and random-access iterators. How do they differ?
    Give an example of a range-based for-loop.
    What is the connection between a range-based for-loop and the begin and end member functions that most container classes have?
    For each of the following STL algorithms, explain what it does and how it is called: std::copy, std::equal, std::sort, std::fill.
    State the Rule of Zero.
    What do we mean by an error condition?
    True or false: When an error condition occurs in a function, the function must inform the caller.
    There are three—and only three—ways to deal with the possibility of an error condition in a function. What are they? Hint: “throwing an exception” is not one of them.
    What does DRY stand for? What does it mean?
    What does it mean when two modules are tightly coupled? Is this a good thing or a bad thing?
    What does it mean for a module to be cohesive? Is this a good thing or a bad thing?
    What is an exception?
    What happens if a C++ exception is thrown, but it is never caught?
    What C++ keyword is used when throwing an exception?
    What C++ syntax do we use to catch every exception, and then rethrow the same exception when we have done what we need to? Be precise & detailed.
    For each statement below, indicate whether you instructor says it is true or false. If true, then explain why he says it is true.
        In C++, constructors should not throw.
        In C++, destructors should not throw.
    Some people dislike exceptions, because using them means that programmers are required to do lots of work. Let us take it as given that (1) exceptions do make lots of work for programmers, and (2) we do not want programmers to be overworked. Nonetheless, your instructor claims that this is a bad reason to dislike exceptions. Why does he say that?
    What do we mean by abstraction?
    In this class, what do we mean by a client of a module?
    What is a Linked List?
    What two pieces of data does a Linked List node hold?
    How do we mark the end of a Linked List?
    An empty Linked List has no nodes. How do we represent an empty Linked List.
    A Linked List holds essentially the same kind of data as an array. Why, then, would we ever want to use a Linked List? We could simply use (smart) arrays for everything, right?
    What is the difference between a Singly Linked List and a Doubly Linked List?
    What does it mean to be recursive?
    What happens if a recursive function never reaches its base case?
    Explain direct vs. indirect recursion.
    Briefly explain how the Binary Search algorithm works.
    In the context of Binary Search, what is a pivot?
    Your instructor says that if we search for an item in a list using operator<, then we should also determine whether we found it using operator<. Why?
    Explain C++ equality vs. equivalence.
    What do std::distance and std::advance do? Explain how using them can be a better choice than doing pointer-arithmetic-style operations on iterators using operators.
    What do we mean by workhorse and wrapper functions?
    What is the call stack? What is a stack frame?
    When is a push done on the call stack? When is a pop done on the call stack? What do these two operations do?
    What is the return address of a function call? Where is it stored?
    What do we mean by an invocation of a function?
    What is the recursion depth of a function call? Why is recursion depth important?
    What are two typical sources of trouble when we use recursion?
    What problems can be caused by excessive recursion depth?
    Given a list of size to search in, at most how many list items does Binary Search need to examine (roughly)?
    Briefly explain how the Sequential Search algorithm works.
    Why is Sequential Search sometimes preferable to Binary Search?
    A quote mentioned during the lecture: “As machines become more powerful, the efficiency of algorithms grows more important, not less.” How can this possibly be true?
    Binary Search requires a sorted list, and it is only efficient if the list is random-access. Sequential Search, on the other hand, works for just about any dataset. Why, then, do we generally prefer Binary Search?
    What is a tail call?
    What does TCO stand for? What does it mean?
    What is tail recursion?
    Why do we like tail recursion? Hint: there might be some irony here.
    What is backtracking?
    What does it mean to say that an algorithm is efficient? This term has both a general and a specific meaning; explain both.
    We are interested in algorithms that use few resources. In this context, what is generally the most important resource?
    What does the term basic operation mean?
    When we analyze an algorithm, we can choose anything we want for our basic operations. What are our usual basic operations, in this class?
    What does it mean for an algorithm (or technique or strategy or …) to be scalable?
    Convert between big- notation and words when describing time efficiency of an algorithm.
    Examples.
        Suppose the order (time efficiency) of some algorithm is . Express this in words.
        Suppose some algorithm is log-linear time. Express this using big- notation.
    Compare efficiency categories, indicating which is faster.
    Examples
        Which is faster, quadratic time or logarithmic time?
    Algorithms faster than linear time are rare. This is because there is a specific thing that such an algorithm cannot do. What is it?
    In our list of efficiency categories, there were two categories that were faster than linear time. Name these two categories.
    Roughly speaking, how slow can an algorithm be and still be considered scalable? Answer using our standard terminology for efficiency categories.
    Briefly explain our “Rule of Thumb” for finding the order of an algorithm involving nested loops.
    In computing, what do we mean by sorting?
    What is a comparison sort?
    In this class, we use the term general-purpose comparison sort. What does this mean?
    What does it mean for an algorithm to be in-place?
    What does it mean for a sorting algorithm to be stable?
    What is the order of Bubble Sort?
    When is Bubble Sort used in practice?
    Explain how Insertion Sort works.
    What is the order of Insertion Sort?
    Is Insertion Sort in-place?
    Is Insertion Sort stable?
    When is Insertion Sort used in practice?
    Bubble Sort and Insertion Sort are both too slow for general-purpose use. Their time efficiency has the same order. And yet, in practice, Insertion Sort does see some use, while Bubble Sort largely does not. Explain.
    Explain big- vs. vs. . How do their meanings differ?
    Given a simple expression, indicate whether it is , , and/or , for some given .
    Examples. For each of the following, indicate whether the given expression is , whether it is , and whether it is .
        .
        .
        .
    Explain the Divide and Conquer algorithmic strategy.
    When do we use the Master Theorem?
    Explain how Merge Sort works.
    What is the order of Merge Sort?
    Is Merge Sort stable?
    Application of the Master Theorem: given a description of a recursive algorithm, find its order. A statement of the Master Theorem will be given.
    Example.
       A recursive algorithm splits its input into two nearly equal-sized parts. It makes a recursive call on each part, and it does other operations amounting to . Using the Master Theorem, find the order of the algorithm. Show your work.
## We can put a limit on the performance of a general-purpose comparison sort. What limit is that?
  nlogn
## Your friend Egbert says, “I have a new general-purpose comparison sort that runs in linear time for all inputs.” Comment on Egbert’s claim.
   He must know more about input data then reasonable for general purpose
    Explain how Quicksort works.
    Is Quicksort stable?
    Quicksort’s Partition operation splits items into the small ones and the large ones. How does the algorithm determine which are small, and which are large?
    We cannot use the Master Theorem to analyze Quicksort. Why not?
## What is the order of Quicksort?
	best: nlogn
	worst: n^2
## Describe one of the commonly used optimizations for Quicksort. What behavior does the algorithm have without the optimization, and how does the optimization change this?
    Different partition scheme. This causes the algo to skip over the data less.
##  What is the average-case order of Quicksort?
    nlog(n)
## In an algorithmic context, what do we mean by introspection?
algo keeps track of its performance 
##What is the order of Introsort?
    best: nlogn
	worst: nlogn
## Is Introsort stable?
	yes


Note. We have not yet covered the material for the following topics.

## Explain how Pigenhole Sort works.
    - First finds high and low items
    - then puts items in buckets and then puts buckets inti list
## What requirements does Pigeonhole Sort place on the data that it sorts?
    - can index data
    What is the order of Pigeonhole Sort?
    - o(n)
    Explain how Radix Sort works.
    - puts items ib backets based on first ubdex
    What requirements does Radix Sort place on the data that it sorts?
    What is the order of Radix Sort?
    Both Pigeonhole Sort and Radix Sort would seem to be faster than it is possible for a sort to be.
        How is this possible?
	- knows info about data
        Why is it not such a big deal?
	- not a big deal because the sors are hard to use
    In the context of C++ lambda functions, what do we mean by capture? When is capturing necessary?
    Is std::sort stable?
    Why do the STL Linked List templates—std::list & std::forward_list—have their own sorting member functions, while other STL containers, like std::vector, do not?


