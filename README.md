# SilentFunctionCaller
Allows for same-file KernelMode function execution using Encrypted addresses of Functions and a custom caller.

This project demonstrates how you can cache risky functions or functions you dont want statically or dynamically traced and encrypt them in a buffer for usage later in the program where they can be decrypted and ran with Template Arguments. How this driver works is when it first runs it caches and encrypts all the addresses set by the user and saves it in a buffer. This buffer will hold multiple of the same (decrypted) address but have multiple versions of its encrypted self, With diferent keys and values.

This is very useful because it makes it extremely difficult almost near impossible to statically trace which functions are doing what (The arguments are a pretty big give-away) and when dynamically tracing its about the same if not harder because of kernel threading and the ability to debug kernel drivers (you cant really) making this useful for ACs and AVs.

Even when you say "Its still loaded at the start of the program" These objects are deleted and the array/buffer is completely random, They wont be able to pick out each function in it.

How this driver identifies Driver Functions & Recognizes them is through their FUNCTION_ID which is set by the user. This is some < 0x100 offset that is just an identifier for the function in its data struct. This is a possible security flaw/vulnerability but I dont say its a big issue because its just a (flag) at best and there is nothing special about it. ACs and AVs look for full pointers & addresses, Not 0x20 & 0x1F flags.

# Plans
- ✅ Call Address Spoofing
- ❌ Condition Address Jumping (if (x) then -> JMP encrypted addr)
- ❌ Add signature scanning for finding address of function to add

![Demo](https://raw.githubusercontent.com/i32-Sudo/SilentFunctionCaller/refs/heads/main/RVK.png)
( Its an ass project made to look good, just doing this for a school project )
Thanks Europapa for encryption <3
