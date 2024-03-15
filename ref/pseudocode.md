node has data and pointer to another node. 
the other node initializes as nullptr

linked list initializes with null pointer. 
length method is just size.

add_left should:

check to see if nullptr
	make head and tail new node.
if not, then grab head and make the new node's pointer object a pointer to it.
then change the pointer in head to be a pointer to the new node


if add right is null, do same as add add_left.
else do the other thing but for the tail.

for both, increase size.

remove right should check again to see if empty. if it is, throw. otherwise,
if one, then just reassign head and tail to nullptr. decrease size, early return
else, go all the way to the end and then do the thing. 


remove left is the same for 0 and 1 size, then it is different because
you only need to go to the tail, get next pointer, reassign tail to this pointer.

string rep should be something like: 
	head -> [element] -> [element] <- tail


testing should have 4 for each one. it should be something like:


when empty
when 1
when 2
when large


probably would be good to also have some tests to make sure some stuff does not break
regarding templating. For instance, I know now that the string function for the 
string template should be specialized because of weirdness surrounding the way that you cannot
cast a std::string to an std::string.

also, when the 
