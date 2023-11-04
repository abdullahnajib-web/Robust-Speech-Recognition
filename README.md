# Robust Speech Recognition System
The thesis on word utterance recognition encompasses various crucial stages of the speech processing pipeline. 
It begins with front-end processing, wherein sampled audio signals are transformed into a collection of vectors through feature extraction. 
In this context, Linear Predictive Coding (LPC) serves as the chosen method for feature extraction. 
The subsequent phase involves sound signal detection, focusing on isolating the target signal while filtering out background noise. 
The methods utilized for detection encompass Energy, Periodicity, and Maximum Likelihood Ratio (MLR) for analyzing periodic and non-periodic noise. 
Once the detection and feature extraction phases are complete, the system proceeds with vector quantization, a process essential for generating a reduced set of vectors capable of representing the untouched vectors. 
Clustering techniques are employed to facilitate vector quantization, with the Linde Buzo Gray (LBG) algorithm taking charge of this operation. 
Finally, the system concludes with a decision-making and comparison stage, implemented through a backpropagation neural network method.

# Architecture

![Arst-SPUK](https://github.com/abdullahnajib-web/Robust-Speech-Recognition/assets/85467959/427df5ca-fb8b-469f-9a3a-46ae4dc11e64)

