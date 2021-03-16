# Digital-Wars
This game was created as a result of the university's course "The Fundamentals of Artificial Intelligence" task.
The AI algorithm includes itself alpha-beta pruning and two heuristic functions: <br />
() one that calculates the difference between each player score, <br />
() the second one checks the sequence of nodes where last child has no childs of his own and each parent has only one child, so-called "the chain of ones". If the depth of last child is equal to foresight count of AI, it returns false (because at this point last child will always have no childs). <br />
The AI implementation you can find in IngameAI files.
