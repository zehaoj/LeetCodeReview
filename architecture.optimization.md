https://www.kaggle.com/cdeotte/how-to-choose-cnn-architecture-mnist


https://www.kaggle.com/michael422/spectrogram-convolution

## Notation
Throughout this file, I'll use the following notation:

**24C5** means a convolution layer with 24 feature maps using a 5x5 filter and stride 1.

**24C5S2** means a convolution layer with 24 feature maps using a 5x5 filter and stride 2.

**D3** means using dropout rate 0.3.

**P2** means max pooling using 2x2 filter and stride 2.

**256** means fully connected dense layer with 256 units

## Input
(20, 30, 40, 50) * (64, 96, 128, 256)

## Depths
* 6400 - **[32C3-P2]** - **[48C3-P2]** - 512 - 1
* 6400 - **[32C3-P2]** - **[48C3-P2]** - **[64C3-P2]** - 512 - 1
* 6400 - **[32C3-P2]** - **[48C3-P2]** - **[64C3-P2]** - **[128C3-P2]** - 512 - 1

## Feature maps

## Dense layer

## Dropout

## Advance
* Replace **P2** with **C5S2** to make it learnable. 
* Add batch normalization.
