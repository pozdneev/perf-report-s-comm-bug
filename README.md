# The issue with `perf report -s comm`
I have the following issue with perf `report -s comm` that I do not fully understand. This is how the code looks like:
```
int main() {
    double a, b, c;
    a = do_things_main(WAIT_TIME * 2); // 40% of time, a.out
    b = do_things1(WAIT_TIME);         // 20% of time, libdo1.so
    c = do_things2(WAIT_TIME * 2);     // 20% of time, libdo2.so
    return (int)(a + b + c);
}
```

This is how I run it:
```
$ LD_LIBRARY_PATH="." perf record -g ./a.out 
[ perf record: Woken up 3 times to write data ]
[ perf record: Captured and wrote 0.743 MB perf.data (11911 samples) ]
```

This is the regular output of `perf report`:
```
$ perf report | grep -v '#' | head -n 12
    39.99%    39.99%  a.out    a.out              [.] main
            |
            ---main

    39.94%    39.94%  a.out    libdo2.so          [.] do_things2
            |
            ---do_things2

    20.05%    20.05%  a.out    libdo1.so          [.] do_things1
            |
            ---do_things1
```

It looks exactly as expected. If I sort by `dso`, the output is also OK:
```
$ perf report -s dso | grep -v '#'
    39.99%    39.99%  a.out            
            |
            ---main

    39.94%    39.94%  libdo2.so        
            |
            ---do_things2

    20.05%    20.05%  libdo1.so        
            |
            ---do_things1
```

However, If I try to sort by `comm`, the output looks strange:
```
$ perf report -s comm | grep -v '#'
   100.00%   100.00%  a.out  
            |          
            |--59.99%--do_things1
            |          
             --39.99%--main
```

If that is OK, how should I read this output? Or is that a bug?

Here is the [full source code of this example](https://github.com/pozdneev/perf-report-s-comm-bug).
Originally, Louis Stuber (IBM Client Center Montpellier) discovered this behaviour when we have been playing with [Flame Graphs](http://www.brendangregg.com/blog/2016-04-30/linux-perf-folded.html).
