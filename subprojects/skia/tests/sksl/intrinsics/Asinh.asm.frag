               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %_entrypoint_v "_entrypoint" %sk_FragColor
               OpExecutionMode %_entrypoint_v OriginUpperLeft
               OpName %sk_FragColor "sk_FragColor"
               OpName %_UniformBuffer "_UniformBuffer"
               OpMemberName %_UniformBuffer 0 "inputVal"
               OpMemberName %_UniformBuffer 1 "expected"
               OpMemberName %_UniformBuffer 2 "colorGreen"
               OpMemberName %_UniformBuffer 3 "colorRed"
               OpName %_entrypoint_v "_entrypoint_v"
               OpName %main "main"
               OpDecorate %sk_FragColor RelaxedPrecision
               OpDecorate %sk_FragColor Location 0
               OpDecorate %sk_FragColor Index 0
               OpMemberDecorate %_UniformBuffer 0 Offset 0
               OpMemberDecorate %_UniformBuffer 0 RelaxedPrecision
               OpMemberDecorate %_UniformBuffer 1 Offset 16
               OpMemberDecorate %_UniformBuffer 1 RelaxedPrecision
               OpMemberDecorate %_UniformBuffer 2 Offset 32
               OpMemberDecorate %_UniformBuffer 2 RelaxedPrecision
               OpMemberDecorate %_UniformBuffer 3 Offset 48
               OpMemberDecorate %_UniformBuffer 3 RelaxedPrecision
               OpDecorate %_UniformBuffer Block
               OpDecorate %7 Binding 0
               OpDecorate %7 DescriptorSet 0
               OpDecorate %25 RelaxedPrecision
               OpDecorate %30 RelaxedPrecision
               OpDecorate %31 RelaxedPrecision
               OpDecorate %34 RelaxedPrecision
               OpDecorate %35 RelaxedPrecision
               OpDecorate %39 RelaxedPrecision
               OpDecorate %41 RelaxedPrecision
               OpDecorate %42 RelaxedPrecision
               OpDecorate %44 RelaxedPrecision
               OpDecorate %45 RelaxedPrecision
               OpDecorate %52 RelaxedPrecision
               OpDecorate %54 RelaxedPrecision
               OpDecorate %55 RelaxedPrecision
               OpDecorate %58 RelaxedPrecision
               OpDecorate %59 RelaxedPrecision
               OpDecorate %66 RelaxedPrecision
               OpDecorate %68 RelaxedPrecision
               OpDecorate %70 RelaxedPrecision
               OpDecorate %78 RelaxedPrecision
               OpDecorate %79 RelaxedPrecision
               OpDecorate %85 RelaxedPrecision
               OpDecorate %86 RelaxedPrecision
               OpDecorate %95 RelaxedPrecision
               OpDecorate %96 RelaxedPrecision
               OpDecorate %105 RelaxedPrecision
               OpDecorate %116 RelaxedPrecision
               OpDecorate %119 RelaxedPrecision
               OpDecorate %120 RelaxedPrecision
      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4
%_ptr_Output_v4float = OpTypePointer Output %v4float
%sk_FragColor = OpVariable %_ptr_Output_v4float Output
%_UniformBuffer = OpTypeStruct %v4float %v4float %v4float %v4float
%_ptr_Uniform__UniformBuffer = OpTypePointer Uniform %_UniformBuffer
          %7 = OpVariable %_ptr_Uniform__UniformBuffer Uniform
       %void = OpTypeVoid
         %12 = OpTypeFunction %void
    %float_0 = OpConstant %float 0
    %v2float = OpTypeVector %float 2
         %16 = OpConstantComposite %v2float %float_0 %float_0
%_ptr_Function_v2float = OpTypePointer Function %v2float
         %20 = OpTypeFunction %v4float %_ptr_Function_v2float
       %bool = OpTypeBool
      %false = OpConstantFalse %bool
%_ptr_Uniform_v4float = OpTypePointer Uniform %v4float
        %int = OpTypeInt 32 1
      %int_0 = OpConstant %int 0
      %int_1 = OpConstant %int 1
     %v2bool = OpTypeVector %bool 2
    %v3float = OpTypeVector %float 3
     %v3bool = OpTypeVector %bool 3
     %v4bool = OpTypeVector %bool 4
    %float_1 = OpConstant %float 1
         %93 = OpConstantComposite %v3float %float_0 %float_0 %float_1
   %float_n1 = OpConstant %float -1
        %103 = OpConstantComposite %v4float %float_0 %float_0 %float_1 %float_n1
%_ptr_Function_v4float = OpTypePointer Function %v4float
      %int_2 = OpConstant %int 2
      %int_3 = OpConstant %int 3
%_entrypoint_v = OpFunction %void None %12
         %13 = OpLabel
         %17 = OpVariable %_ptr_Function_v2float Function
               OpStore %17 %16
         %19 = OpFunctionCall %v4float %main %17
               OpStore %sk_FragColor %19
               OpReturn
               OpFunctionEnd
       %main = OpFunction %v4float None %20
         %21 = OpFunctionParameter %_ptr_Function_v2float
         %22 = OpLabel
        %109 = OpVariable %_ptr_Function_v4float Function
         %26 = OpAccessChain %_ptr_Uniform_v4float %7 %int_0
         %30 = OpLoad %v4float %26
         %31 = OpCompositeExtract %float %30 0
         %25 = OpExtInst %float %1 Asinh %31
         %32 = OpAccessChain %_ptr_Uniform_v4float %7 %int_1
         %34 = OpLoad %v4float %32
         %35 = OpCompositeExtract %float %34 0
         %36 = OpFOrdEqual %bool %25 %35
               OpSelectionMerge %38 None
               OpBranchConditional %36 %37 %38
         %37 = OpLabel
         %40 = OpAccessChain %_ptr_Uniform_v4float %7 %int_0
         %41 = OpLoad %v4float %40
         %42 = OpVectorShuffle %v2float %41 %41 0 1
         %39 = OpExtInst %v2float %1 Asinh %42
         %43 = OpAccessChain %_ptr_Uniform_v4float %7 %int_1
         %44 = OpLoad %v4float %43
         %45 = OpVectorShuffle %v2float %44 %44 0 1
         %46 = OpFOrdEqual %v2bool %39 %45
         %48 = OpAll %bool %46
               OpBranch %38
         %38 = OpLabel
         %49 = OpPhi %bool %false %22 %48 %37
               OpSelectionMerge %51 None
               OpBranchConditional %49 %50 %51
         %50 = OpLabel
         %53 = OpAccessChain %_ptr_Uniform_v4float %7 %int_0
         %54 = OpLoad %v4float %53
         %55 = OpVectorShuffle %v3float %54 %54 0 1 2
         %52 = OpExtInst %v3float %1 Asinh %55
         %57 = OpAccessChain %_ptr_Uniform_v4float %7 %int_1
         %58 = OpLoad %v4float %57
         %59 = OpVectorShuffle %v3float %58 %58 0 1 2
         %60 = OpFOrdEqual %v3bool %52 %59
         %62 = OpAll %bool %60
               OpBranch %51
         %51 = OpLabel
         %63 = OpPhi %bool %false %38 %62 %50
               OpSelectionMerge %65 None
               OpBranchConditional %63 %64 %65
         %64 = OpLabel
         %67 = OpAccessChain %_ptr_Uniform_v4float %7 %int_0
         %68 = OpLoad %v4float %67
         %66 = OpExtInst %v4float %1 Asinh %68
         %69 = OpAccessChain %_ptr_Uniform_v4float %7 %int_1
         %70 = OpLoad %v4float %69
         %71 = OpFOrdEqual %v4bool %66 %70
         %73 = OpAll %bool %71
               OpBranch %65
         %65 = OpLabel
         %74 = OpPhi %bool %false %51 %73 %64
               OpSelectionMerge %76 None
               OpBranchConditional %74 %75 %76
         %75 = OpLabel
         %77 = OpAccessChain %_ptr_Uniform_v4float %7 %int_1
         %78 = OpLoad %v4float %77
         %79 = OpCompositeExtract %float %78 0
         %80 = OpFOrdEqual %bool %float_0 %79
               OpBranch %76
         %76 = OpLabel
         %81 = OpPhi %bool %false %65 %80 %75
               OpSelectionMerge %83 None
               OpBranchConditional %81 %82 %83
         %82 = OpLabel
         %84 = OpAccessChain %_ptr_Uniform_v4float %7 %int_1
         %85 = OpLoad %v4float %84
         %86 = OpVectorShuffle %v2float %85 %85 0 1
         %87 = OpFOrdEqual %v2bool %16 %86
         %88 = OpAll %bool %87
               OpBranch %83
         %83 = OpLabel
         %89 = OpPhi %bool %false %76 %88 %82
               OpSelectionMerge %91 None
               OpBranchConditional %89 %90 %91
         %90 = OpLabel
         %94 = OpAccessChain %_ptr_Uniform_v4float %7 %int_1
         %95 = OpLoad %v4float %94
         %96 = OpVectorShuffle %v3float %95 %95 0 1 2
         %97 = OpFOrdEqual %v3bool %93 %96
         %98 = OpAll %bool %97
               OpBranch %91
         %91 = OpLabel
         %99 = OpPhi %bool %false %83 %98 %90
               OpSelectionMerge %101 None
               OpBranchConditional %99 %100 %101
        %100 = OpLabel
        %104 = OpAccessChain %_ptr_Uniform_v4float %7 %int_1
        %105 = OpLoad %v4float %104
        %106 = OpFOrdEqual %v4bool %103 %105
        %107 = OpAll %bool %106
               OpBranch %101
        %101 = OpLabel
        %108 = OpPhi %bool %false %91 %107 %100
               OpSelectionMerge %113 None
               OpBranchConditional %108 %111 %112
        %111 = OpLabel
        %114 = OpAccessChain %_ptr_Uniform_v4float %7 %int_2
        %116 = OpLoad %v4float %114
               OpStore %109 %116
               OpBranch %113
        %112 = OpLabel
        %117 = OpAccessChain %_ptr_Uniform_v4float %7 %int_3
        %119 = OpLoad %v4float %117
               OpStore %109 %119
               OpBranch %113
        %113 = OpLabel
        %120 = OpLoad %v4float %109
               OpReturnValue %120
               OpFunctionEnd
