# SilentFunctionCaller
Allows for same-file KernelMode function execution using Encrypted addresses of Functions and a custom caller.

This project demonstrates how you can cache risky functions or functions you dont want statically or dynamically traced and encrypt them in a buffer for usage later in the program where they can be decrypted and ran with Template Arguments. How this driver works is when it first runs it caches and encrypts all the addresses set by the user and saves it in a buffer. This buffer will hold multiple of the same (decrypted) address but have multiple versions of its encrypted self, With diferent keys and values.

This is very useful because it makes it extremely difficult almost near impossible to statically trace which functions are doing what (The arguments are a pretty big give-away) and when dynamically tracing its about the same if not harder because of kernel threading and the ability to debug kernel drivers (you cant really) making this useful for ACs and AVs.

Even when you say "Its still loaded at the start of the program" These objects are deleted and the array/buffer is completely random, They wont be able to pick out each function in it.
