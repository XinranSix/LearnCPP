## 前置知识

计算机的指令集一般可分为 4 种：

- 复杂指令集（CISC）
- 精简指令集 （ RISC）
- 显 式 并 行 指 令 集 （ EPIC ） 
- 超 长 指 令 字 指 令 集（VLIW）

我们在嵌入式学习和工作中需要经常打交道的是 RISC 指令集。RISC 指令集相对于 CISC 指令集，主要有以下特点：

- Load / Store架构，CPU 不能直接处理内存中的数据，要先将内存中的数据 Load（加载）到寄存器中才能操作，然后将处理结果 Store（存储）到内存中。
- 固定的指令长度、单周期指令。
- 倾向于使用更多的寄存器来存储数据，而不是使用内存中的堆栈，效率更高。

ARM 指令集虽然属于 RISC，但是和原汁原味的 RISC 相比，还是有一
些差异的，具体如下：

- ARM 有桶型移位寄存器，单周期内可以完成数据的各种移位操作。
- **并不是所有的 ARM 指令都是单周期的。**
- ARM 有 16 位的 Thumb 指令集，是 32 位 ARM 指令集的压缩形式，提高了代码密度。
- 条件执行：通过指令组合，减少了分支指令数目，提高了代码密度。
- 增加了 DSP、SIMD / NEON 等指令。

ARM 处理器有多种工作模式，如下图所示。应用程序正常运行时，ARM 处理器工作在用户模式（User mode），当程序运行出错或有中断发生时，ARM 处理器就会切换到对应的特权工作模式。用户模式属于普通模式，有些特权指令是运行不了的，需要切换到特权模式下才能运行。在 ARM 处理器中，除了用户模式是普通模式，剩下的几种工作模式都属于特权模式。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/7059623d-ec4c-473f-b6dd-cc592303c1b7)

在 ARM 处理器内部，除了基本的算术运算单元、逻辑运算单元、浮点运算单元和控制单元，还有一系列寄存器，包括各种通用寄存器、状态寄存器、控制寄存器，用来控制处理器的运行，保存程序运行时的各种状态和临时结果，如下图所示：

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/2fbec729-8e2e-477d-9f8b-a5bb2804262f)

ARM 处理器中的寄存器可分为通用寄存器和专用寄存器两种。寄存器 R0～R12 属于通用寄存器，除了 FIQ 工作模式，在其他工作模式下这些寄存器都是共用、共享的：R0～R3 通常用来传递函数参数，R4～R11 用来保存程序运算的中间结果或函数的局部变量等，R12 常用来作为函数调用过程中的临时寄存器。ARM 处理器有多种工作模式，除了这些在各个模式下通用的寄存器，还有一些寄存器在各自的工作模式下是独立存在的，如 R13、R14、R15、CPSP、SPSR 寄存器，在每个工作模式下都有自己单独的寄存器。R13 寄存器又称为堆栈指针寄存器（Stack Pointer，SP），用来维护和管理函数调用过程中的栈帧变化，R13 总是指向当前正在运行的函数的栈帧，一般不能再用作其他用途。R14 寄存器又称为链接寄存器（Link Register，LR），在函数调用过程中主要用来保存上一级函数调用者的返回地址。寄存器 R15 又称为程序计数器（Program Counter，PC），CPU 从内存取指令执行，就是默认从 PC 保存的地址中取的，每取一次指令，PC 寄存器的地址值自动增加。CPU 一条一条不停地取指令，程序也就源源不断地一直运行下去。在 ARM 三级流水线中，PC 指针的值等于当前正在运行的指令地 +8，后续的 32 位处理器虽然流水线的级数不断增加，但为了简化编程，PC 指针的值继续延续了这种计算方式。

当前处理器状态寄存器（Current Processor State Register，CPSR）主要用来表征当前处理器的运行状态。除了各种状态位、标志位，CPSR 寄存器里也有一些控制位，用来切换处理器的工作模式和中断使能控制。CPSR 寄存器各个标志位、控制位的详细说明下图所示：

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/0e3f3e48-8ce0-46aa-9d89-f212df6b883b)

在每种工作模式下，都有一个单独的程序状态保存寄存器（Saved Processor State Register，SPSR）。当 ARM 处理器切换工作模式或发生异常时，SPSR 用来保存当前工作模式下的处理器现场，即将 CPSR 寄存器的值保存到当前工作模式下的 SPSR 寄存器。当 ARM 处理器从异常返回时，就可以从 SPSR 寄存器中恢复原先的处理器状态，切换到原来的工作模式继续运行。

在 ARM 所有的工作模式中，有一种工作模式比较特殊，即 FIQ 模式。为了快速响应中断，减少中断现场保护带来的时间开销，在 FIQ 工作模式下，ARM处理器有自己独享的 R8～R12 寄存器。

## ARM 汇编指令

一个完整的 ARM 指令通常由**操作码 + 操作数**组成，指令的编码格式如下：

```arm
<opcode> {<code> {S} <Rd>, <Rn> {, <operand2>}}
```

这是一个完整的 ARM 指令需要遵循的格式规则，指令格式的具体说明如下：

- 使用 `<>` 标起来的是必选项，使用 `{}` 标起来的是可选项。
- `<opcode>` 是二进制机器指令的操作码助记符，如 `MOV`、`ADD` 这些汇编指令都是操作码的指令助记符。
- `cond`：执行条件，ARM 为减少分支跳转指令个数，允许类似 `BEQ`、`BNE` 等形式的组合指令。
- `S`：是否影响 CPSR 寄存器中的标志位，如 SUBS 指令会影响 CPSR 寄存器中的 N、Z、C、V 标志位，而 SUB 指令不会。
- `Rd`：目标寄存器。
- `Rn`：第一个操作数的寄存器。
- `operand2`：第二个可选操作数，灵活使用第二个操作数可以提高代码效率。

### 存储访问指令

ARM 指令集属于 RISC 指令集，RISC 处理器采用典型的加载/存储体系结构，CPU 无法对内存里的数据直接操作，只能通 Load / Store 指令来实现：当我们需要对内存中的数据进行操作时，要首先将这个数据从内存加载到寄存器，然后在寄存器中对数据进行处理，最后将结果重新存储到内存中。

ARM 处理器属于冯·诺依曼架构，程序和数据都存储在同一存储器上，内存空间和 I/O 空间统一编址，ARM 处理器对程序指令、数据、I/O 空间中外设寄存器的访问都要通过 Load/Store 指令来完成。ARM 处理器中经常使用的 Load/Store 指令的使用方法如下。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/2ff6eaef-147d-4815-b1e5-51014f28cfe5)

在 ARM 存储访问指令中，我们经常使用的是 LDR/STR、LDM/STM 这两对指令。LDR/STR 指令是 ARM 汇编程序中使用频率最高的一对指令，每一次数据的处理基本上都离不开它们。LDM/STM 指令常用来加载或存储一组寄存器到一片连续的内存，通过和堆栈格式符组合使用，LDM/STM 指令还可以用来模拟堆栈操作。LDM/STM 指令常和下表的堆栈格式组合使用：

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/4a6e20a4-2630-4466-9765-6d8660b4d6c3)

如图3-3所示，在一个堆栈内存结构中，如果堆栈指针 SP 总是指向栈顶元素，那么这个栈就是满栈；如果堆栈指针 SP 指向的是栈顶元素的下一个空闲的存储单元，那么这个栈就是空栈。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/24b7757d-999b-4056-938e-8333a9a4816d)

每入栈一个元素，栈指针 SP 都会往栈增长的方向移动一个存储单元。如果栈指针 SP 从高地址往低地址移动，那么这个栈就是递减栈；如果栈指针 SP 从低地址往高地址移动，那么这个栈就是递增栈。ARM 处理器使用的一般都是满递减堆栈，在将一组寄存器入栈，或者从栈中弹出一组寄存器时，我们可以使用下面的指令。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/f8a0c6d1-ad66-466f-86e1-9b6b63046408)

这里需要注意的一个细节是，在入栈和出栈过程中要留意栈中各个元素的入栈出栈顺序。栈的特点是先入后出（First In Last Out，FILO），栈元素在入栈操作时，STMFD 会根据大括号 `{}` 中寄存器列表中各个寄存器的顺序，从左往右依次压入堆栈。在上面的例子中，R0 会先入栈，接着 R1、R2 入栈，最后 R14 入栈，入栈操作完成后，栈指针 SP 在内存中的位置如图 3-4 左侧所示。栈元素在出栈操作时，顺序刚好相反，栈中的元素先弹出到 R14 寄存器中，接着是 R2、R1、R0。将栈中的元素依次弹出到 R14、R2 寄存器后，堆栈指针在内存中的位置如图3-4右侧所示。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/4f3d58b9-a7d2-43a9-b930-12d616bd6e69)

除此之外，ARM 还专门提供了 PUSH 和 POP 指令来执行栈元素的入栈和出栈操作。PUSH 和 POP 指令的使用方法如下：

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/44cfc5d7-eb03-41a3-8721-a95305014d7f)

### 数据传送指令

LDR/STR 指令用来在寄存器和内存之间输送数据。如果我们想要在寄存器之间传送数据，则可以使用 MOV 指令。MOV 指令的格式如下：

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/14355230-5433-48e6-927e-deab72902f19)

其中，`{cond}` 为条件指令可选项，`{S}` 用来表示是否影响 CPSR 寄存器的值，如 MOVS 指令就会影响寄存器 CPSR 的值，而 MOV 则不会。

MVN 指令用来将操作数 operand2 按位取反后传送到目标寄存器 Rd。操作数 operand2 可以是一个立即数，也可以是一个寄存器。

MOV 和 MVN 指令的一般使用方法如下：

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/6f681bd5-7e86-4a23-842f-c4e142b2b6af)

### 算术逻辑运算指令

算术运算指令包括基本的加、减、乘、除，逻辑运算指令包括与、或、非、异或、清除等。指令格式如下。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/79a6eaa2-57c2-491b-ba21-f9490fdd0038)

算术逻辑运算指令的基本使用方法及说明如下。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/e023cb2e-fa28-44a2-9bbd-9c67e3285d0b)

### 操作数：operand2 详解

ARM 指令的可选项很多，操作数也很灵活。很多 ARM 指令会使用第 2 个参数 operand2：可以是一个常数，也可以是寄存器+偏移的形式。

操作数 operand2 在汇编程序中经常出现的两种格式如下：

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/670567f6-0f40-4adf-85f8-388b78e29cc9)

第一种格式比较简单，操作数是一个立即数，第二种格式可以直接使用寄存器的值作为操作数。

`ADD`、`SUB`、`AND` 指令示例中，第二个操作数要么是一个常数，要么是一个寄存器。在第二种格式中，通过 `{，shift}` 可选项，我们还可以通过多种移位或循环移位的方式，构建更加灵活的操作数。可选项 `{，shift}` 可以选择的移位方式如下。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/9ed294d1-cd66-46da-9be7-09329c8228e0)

可选性指令的使用示例及说明如下：

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/e01e4b37-f585-4cff-aa7e-1aae71d5ebf0)

### 比较指令

比较指令用来比较两个数的大小，或比较两个数是否相等。比较指令的运算结果会影响 CPSR 寄存器的 N、Z、C、V 标志位，具体的标志、位说明可参考前面的 CPSR 寄存器介绍。

比较指令的格式如下：

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/d1a40e26-faa9-441c-a003-6a5d35cf36e6)

比较指令的使用示例及说明如下：

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/33bee05a-a3d9-4a07-afd5-2e1f2756a303)

比较指令的运行结果 Z=1 时，表示运算结果为零，两个数相等；N=1 表示运算结果为负，N=0 表示运算结果为非负，即运算结果为正或者为零。

### 条件执行指令

为了提高代码密度，减少 ARM 指令的数量，几乎所有的 ARM 指令都可以根据 CPSR 寄存器中的标志位，通过指令组合实现条件执行。如无条件跳转指令 B，我们可以在后面加上条件码组成 BEQ、BNE 组合指令。

BEQ 指令表示两个数比较，结果相等时跳转；BNE 指令则表示结果不相等时跳转。CPSR 寄存器中的标志位根据需要可以任意搭配成不同的条件码，和 ARM 指令一起组合使用。

ARM 指令的条件码如表3-3所示：

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/08284c0f-d520-44bc-9aa3-02dfa66f44c8)

条件执行经常出现在跳转或循环的程序结构中。如下面的汇编程
序，通过循环结构，我们可以实现数据块的搬运功能。我们可以将无条件跳转指令 B 和条件码 NE 组合在一起使用，构成一个循环程序结构。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/f2266b5e-6b35-435a-ad37-7fa42974b0c4)

### 跳转指令

在函数调用的场合，以及循环结构、分支结构的程序中经常会用
到跳转指令。ARM 指令集提供了 `B`、`BL`、`BX`、`BLX`` 等跳转指令，每个指令都有各自的用武之地和使用场景。

跳转指令的格式如下：

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/3962c140-0876-473d-a460-87be2dc695a6)

#### B label

跳转到标号 label 处，B 跳转指令的跳转范围大小为[0，32MB]，可以往前跳，也可以往后跳。无条件跳转指令 B 主要用在循环、分支结构的汇编程序中，使用示例如下：

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/c4a44fc3-65d4-4900-b669-f30e6d35a612)

#### BL label

BL 跳转指令表示带链接的跳转。

在跳转之前，BL 指令会先将当前指令的下一条指令地址（即返回地址）保存到 LR 寄存器中，然后跳转到 label 处执行。

BL 指令一般用在函数调用的场合，主函数在跳转到子函数执行之前，会先将返回地址，即当前跳转指令的下一条指令地址保存到 LR 寄存器中；子函数执行结束后，LR 寄存器中的地址被赋值给 PC，处理器就可以返回到原来的主函数中继续运行了。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/32056188-99a5-4044-aa38-df9a7d06a043)

#### BX Rm

BX 表示带状态切换的跳转。

Rm 寄存器中保存的是跳转地址，要跳转的目标地址处可能是 ARM 指令，也可能是 Thumb 指令。处理器根据 Rm[0] 位决定是切换到 ARM 状态还是切换到 Thumb 状态。

- 0：表示目标地址处是 ARM 指令，在跳转之前要先切换至 ARM 状态。 
- 1：表示目标地址处是 Thumb 指令，在跳转之前要先切换至 Thumb 状态。BLX 指令是 BL 指令和 BX 指令的综合，表示带链接和状态切换的跳转，使用方法和上面相同，不再赘述。

## ARM 寻址方式

ARM 属于 RISC 体系架构，一个 ARM 汇编程序中的大部分汇编指令，基本上都和数据传输有关：在内存-寄存器、内存-内存、寄存器-寄存器之间来回传输数据。不同的 ARM 指令又有不同的寻址方式，比较常见的寻址方式有寄存器寻址、立即寻址、寄存器偏移寻址、寄存器间接寻址、基址寻址、多寄存器寻址、相对寻址等。

### 寄存器寻址

寄存器寻址比较简单，操作数保存在寄存器中，通过寄存器名就可以直接对寄存器中的数据进行读写。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/eb0bf15a-0c26-41bf-a569-73a632ea5a66)

### 立即数寻址

在立即数寻址中，ARM 指令中的操作数为一个常数。立即数以 ＃ 为前缀，0x 前缀表示该立即数为十六进制，不加前缀默认是十进制。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/84c6864e-7512-4e11-8ab4-aaa9f408dac5)

### 寄存器偏移寻址

寄存器偏移寻址可以看作寄存器寻址的一种特例，通过第二个操作数 operand2 的灵活配置，我们可以将第二个操作数做各种左移和右移操作，作为新的操作数使用。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/6d9f7d6d-7229-4461-a85a-448cfe7471c0)

常见的移位操作有逻辑移位和算术移位，两者的区别是：逻辑移位无论是左移还是右移，空缺位一律补 0；而算术移位则不同，左移时空缺位补 0，右移时空缺位使用符号位填充。

### 寄存器间接寻址

寄存器间接寻址主要用来在内存和寄存器之间传输数据。寄存器中保存的是数据在内存中的存储地址，我们通过这个地址就可以在寄存器和内存之间传输数据。C 语言中的指针操作，在汇编层次其实就是使用寄存器间接寻址实现的。寄存器间接寻址的使用示例及说明如下所示。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/06d0cfd1-8274-4523-9777-b2772ae8ccf9)

### 基址寻址

基址寻址其实也属于寄存器间接寻址。两者的不同之处在于，基址寻址将寄存器中的地址与一个偏移量相加，生成一个新地址，然后基于这个新地址去访问内存。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/d107f147-5f08-46fd-aacc-2f6d1f2bde0c)

基址寻址一般用在查表、数组访问、函数的栈帧管理等场合。根据偏移量的正负，基址寻址又可以分为向前索引寻址和向后索引寻址，如上面的第 1 条和第 3 条指令，就是向后索引寻址，而第6条指令则为向前索引寻址。

### 多寄存器寻址

STM/LDM 指令就属于多寄存器寻址，一次可以传输多个寄存器的值。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/5d43bfe1-a2e3-4017-bbc2-65b23e668453)

在多寄存器寻址中，用大括号 `{}` 括起来的是寄存器列表，寄存器之间用逗号隔开，如果是连续的寄存器，还可以使用连接符-连接，如 R0-R3，就表示 R0、R1、R2、R3 这 4 个寄存器。

LDM/STM 指令一般和 IA、IB、DA、DB 组合使用，分别表示 Increase After、Increase Before、Decrease After、Decrease Before。

LDM/STM 指令也可以和 FD、ED、FA、EA 组合使用，用于堆栈操作。

栈是程序运行过程中非常重要的一段内存空间，栈是 C 语言运行的基础，函数内的局部变量、函数调用过程中要传递的参数、函数的返回值一般都是保存在栈中的。

ARM 没有专门的入栈和出栈指令，ARM 中的栈操作其实就是通过上面所讲的 STM/LDM 指令和栈指针 SP 配合操作完成的。栈一般可以分为以下 4 类：

- 递增栈 A：入栈时，SP 栈指针从低地址往高地址方向增长。
- 递减栈 D：入栈时，SP 栈指针从高地址往低地址方向增长。
- 满栈 F：SP 栈指针总是指向栈顶元素。
- 空栈 E：SP 栈指针总是指向栈顶元素的下一个空闲存储单元。

ARM 默认使用满递减堆栈，通过 STMFD/LDMFD 指令配对使用，完成堆栈的入栈和出栈操作。

ARM 中的 PUSH 和 POP 指令其实就是 LDM/STM 的同义词，是 LDMFD 和 STMFD 组合指令的助记符。

PUSH 指令和 POP 指令的使用示例如下：

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/1f106995-cf0d-46bf-999a-c5ccd62a135d)

### 相对寻址

相对寻址其实也属于基址寻址，只不过它是基址寻址的一种特殊
情况。特殊在什么地方呢？它是以 PC 指针作为基地址进行寻址的，以指令中的地址差作为偏移，两者相加后得到的就是一个新地址，然后可以对这个地址进行读写操作。

ARM 中的 B、BL、ADR 指令其实都是采用相对寻址的。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/682acaa6-6c3b-40e5-b9c2-4c695eb0f3d2)

在上面的示例代码中，B LOOP 指令其实就等价于：

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/6bb5563d-7e93-4cfa-a329-d08c6b51de46)

除此之外，很多与位置无关的代码，如动态链接共享库，其在汇编代码层次的实现其实也是采用相对寻址的。程序中使用相对寻址访问的好处是不需要重定位，将代码加载到内存中的任何地址都可以直接运行。

## ARM 伪指令

ARM 伪指令并不是 ARM 指令集中定义的标准指令，而是为了编程方便，各家编译器厂商自定义的一些辅助指令。

伪指令有点类似 C 语言中的预处理命令，在程序编译时，这些伪
指令会被翻译为一条或多条 ARM 标准指令。

常见的 ARM 伪指令主要有 4 个：ADR、ADRL、LDR、NOP，它们的使用示例如下：

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/4a12f423-5440-4198-a6b1-5b1a9f978f31)

NOP 伪指令比较简单，其实就相当于 MOV R0，R0。

在以后的学习和工作中，大家在 ARM 汇编程序中经常看到的就是 LDR 伪指令。

### LDR 伪指令

LDR 伪指令通常会让很多朋友感到迷惑，容易和加载指令 LDR 混淆。

LDR 伪指令的主要用途是将一个 32 位的内存地址保存到寄存器中。

在寄存器之间传递数据可以使用 MOV 指令，但是当传递的一个内存地址是 32 位的立即数时，MOV 指令就应付不了了，如下面的第 2 条指令。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/a8d5ce2d-05b6-4136-8cce-a66f082ad0e6)

当我们往寄存器传递的地址是一个 32 位的常数时，为什么不能使用 MOV，而要使用 LDR 伪指令呢？这还得从 ARM 指令的编码格式说起。

RISC 指令的特点是单周期指令，指令的长度一般都是固定的。在一个 32 位的系统中，一条指令通常是 32 位的，指令中包括操作码和操作数，如图3-5所示：

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/8cf1c334-6199-4c1f-be9d-a97b7c49add8)

指令中的操作码和操作数共享 3 2位的存储空间：一般前面的操作码要占据几个比特位，剩下来的留给操作数的编码空间就小 32 位了。

当编译器遇到 `MOV R0，＃0x30008000` 这条指令时，因为后面的操作数是 32 位，编译器就无法对这条指令进行编码了。为了解决这个难题，编译器提供了一个 LDR 伪指令来完成上面的功能。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/dbbce217-c541-488c-b905-d2d0e2030e43)

在上面的示例代码中，LDR 不是普通的 ARM 加载指令，而是一个伪指令。为了与 ARM 指令集中的加载指令 LDR 区别开来，**LDR 伪指令中的操作数前一般会有一个等于号=**，用来表示该指令是个伪指令。

通过 LDR 伪指令，编译器就解决了向一个寄存器传送 32 位的立即数时指令无法编码的难题。

因为伪指令并不是 ARM 指令集中定义的标准指令，所以 CPU 硬件译码电路并不支持直接运行这些伪指令。

在程序编译期间，这些伪指令会被标准的 ARM 指令替代。

编译器在处理伪指令时，根据伪指令中的操作数大小，会使用不同的 ARM 标准指令替代。

如当 LDR 伪指令中的操作数小于 8 位时，LDR 伪指令一般会被 MOV 指令替代。下面的两行汇编指令其实是等价的：

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/076072b8-7b10-421c-8d29-9da2ad9c1d0f)

当 LDR 伪指令中的操作数大于 8 位时，LDR 指令会被编译器转换为 `LDR 标准指令+文字池` 的形式。

![image](https://github.com/XinranSix/Computer-Graphics/assets/62458905/f6505634-6ec4-41cf-92c7-1906d46ac9fc)















