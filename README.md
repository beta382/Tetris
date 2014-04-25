#Tetris

Group project for CSI 1440 - Freshman Spring Semester

For complete documentation, check out the source code.

###How to use leakcheck

It's super simple. In the header(s) of the object(s) you want to monitor, include `"util.cpp"` add the following code under `public`:

```c++
void* operator new(size_t bytes) {
    return leakcheck::alloc(bytes, "NAME_OF_YOUR_OBJECT");
}

void operator delete(void* mem) {
    leakcheck::dealloc(mem);
}
```

`NAME_OF_YOUR_OBJECT` is a string representation of what you call your object, although you can make it whatever you want.
The allocations will get logged with the name that you provide.

To output the tracked objects currently on the heap to the console, insert:

```c++
leakcheck::print(cout);
```

somewhere in your code.

To show a summary when your program dies, add the following code before an exit point (either the end of main or a call to `exit(int)`):

```c++
cout << "n_new:    " << leakcheck::n_new << endl;
cout << "n_delete: " << leakcheck::n_delete << endl;
cout << endl;
cout << "leaking " << leakcheck::bytes() << " bytes from " << leakcheck::allocated.size() << " objects" << endl;
cout << endl;
leakcheck::print(cout);
```

For best results, make sure that all dynamically allocated data is deleted prior to sumarizing and exiting. This
includes forcing objects you know are dynamically allocated to commit suicide (`delete this;`) if control will reach a
call to `exit(int)` from within the object.
