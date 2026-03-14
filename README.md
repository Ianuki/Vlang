# ViLang
A minimal, statically-typed, low-level systems language
Expected to support x86, AVR, my custom ISA and maybe Wasm

## Reasons to code in VI

This is a snippet of C code (virgin, very unsafe), it causes multiple memory leaks (computer crash). It's inconsistent and ugly and overall just worse.
```c
void function_that_goes_terribly_wrong(void nothing) {
    (void***)malloc(sizeof(size_t) * 0xFFFFFFFF) /* Heap spraying to show whos the boss */

    exit(1);    /* Optimal error handling, printfing the error is highly advised */
    return 1;   /* Inferior, less optimized wannabe exception (this ain't java) */
}

uint64_t xd;
```

Now, compare it with a snippet of VI code (chad, safe, free overhead and memory leaks). Notice how thee syntax is much more sweeter and inviting and makes you want to only use VI for the rest of your life (it's the best option)
```lua
push i: U64; set i = 1 /* Tuff variable initialization */

repeat /* Loop repeats forever to ensure turing completeness remains debunked */
    set i = i + 1 
    
    if i == 0
        break
    end
end
```

This project is stupid and im only working on it because i got nothing better to do\
I'm hoping to get a functional build before the month is out\
(i'm stuck at generating the AST)\
![](https://github.com/Ianuki/ViLang/blob/main/Gimli_success.gif)
