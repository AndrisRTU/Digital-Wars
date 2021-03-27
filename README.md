# Digital-Wars
This game was created as a result of the university's course "The Fundamentals of Artificial Intelligence" task.
The AI algorithm includes itself alpha-beta pruning and two heuristic functions: <br />
() one that calculates the difference between each player score, <br />
() the second one checks if the last child has no childs. If the depth of last child is equal to foresight count of AI, it returns 0 (because at this point the last child will always have no childs). If score difference is more or equal to 0, 999 is returned, otherwise -999 is returned. <br />
The AI implementation you can find in IngameAI files.
