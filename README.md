
this a custom build of  PyS60 1.4.5 for S60v3 . that can run on EKA2L1 emulator. (tested with nokia 5320XM ROM)

it was basically built without

USE_STACKCHECK  , since a call to  PyOS_CheckStack() / e32_check_stack()  (in ceval.c),  will always return -1 . causing the interpreter to exit with "Stack overflow" error.

### Note : the above issue was test only on EKA2L for Android.

and there is another problem, on EKA2L1 (i think with CFbsBitmap) , PyS60 graphics module. cannot render fonts/images properly. (scripts that draw  text directly on the Canvas looks fine).

### Download

[Python.sis](./Python.sis)  contains the interpreter and the runtime libraries +  a simple script launcher , to test/run some GUI modules/utilities , and some games like : 

- Snake by Nokia.

- Martian Tanks (dimonvideo.ru).

- PyJumble by  Pavan Pareta (croozeus.com).

- Jomtris by  Jouni Miettunen (croozeus.com).

- kaka puzzle (dimonvideo.ru).

- NgebutQD by (Tigan)

