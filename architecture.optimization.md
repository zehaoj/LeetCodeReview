https://www.kaggle.com/cdeotte/how-to-choose-cnn-architecture-mnist

https://blog.keras.io/building-powerful-image-classification-models-using-very-little-data.html

https://www.kaggle.com/michael422/spectrogram-convolution

## Notation
Throughout this file, I'll use the following notation:

**24C5** means a convolution layer with 24 feature maps using a 5x5 filter and stride 1.

**24C5S2** means a convolution layer with 24 feature maps using a 5x5 filter and stride 2.

**D3** means using dropout rate 0.3.

**P2** means max pooling using 2x2 filter and stride 2.

**256** means fully connected dense layer with 256 units

## Input
(20, 35, 50) * (64, 96, 128)

## Depths
* 6400 - **[32C3-P2]** - **[64C3-P2]** - 512 - 1
* 6400 - **[32C3-P2]** - **[64C3-P2]** - **[128C3-P2]** - 512 - 1
* 6400 - **[32C3-P2]** - **[64C3-P2]** - **[128C3-P2]** - **[256C3-P2]** - 512 - 1

```python
model = [0] * 3
for i in range(3):
    model[i] = Sequential()
    model[i].add(Conv2D(filters=32, kernel_size=(3, 3), activation='relu', padding='same', input_shape=(50, 128, 2)))
    model[i].add(MaxPooling2D(pool_size=(2, 2)))
    
    model[i].add(Conv2D(filters=64, kernel_size=(3, 3), padding='same', activation='relu'))
    model[i].add(MaxPooling2D(pool_size=(2, 2)))
    
    if (i > 0):
        model[i].add(Conv2D(filters=128, kernel_size=(3, 3), padding='same', activation='relu'))
        model[i].add(MaxPooling2D(pool_size=(2, 2)))
    if (i > 1):
        model[i].add(Conv2D(filters=256, kernel_size=(3, 3), padding='same', activation='relu'))
        model[i].add(MaxPooling2D(pool_size=(2, 2)))
    
    model[i].add(Flatten())
    model[i].add(Dense(512, activation='relu'))
    model[i].add(Dropout(0.3))
    model[i].add(Dense(1, activation='sigmoid'))
    model[i].compile(loss='mean_squared_error', optimizer=Adam(lr=0.0005, beta_1=0.9, beta_2=0.999), metrics=['accuracy'])
    
# CREATE VALIDATION SET
X_train2, X_val2, Y_train2, Y_val2 = train_test_split(X_train, Y_train, test_size = 0.333)
# TRAIN NETWORKS
history = [0] * 3
names = ["(C-P)x2","(C-P)x3","(C-P)x4"]
epochs = 30
for j in range(3):
    history[j] = model[j].fit(X_train2,Y_train2, batch_size=80, epochs = epochs, 
        validation_data = (X_val2,Y_val2), callbacks=[annealer], verbose=0)
    print("CNN {0}: Epochs={1:d}, Train accuracy={2:.5f}, Validation accuracy={3:.5f}".format(
        names[j],epochs,max(history[j].history['acc']),max(history[j].history['val_acc']) ))
        
# PLOT ACCURACIES
plt.figure(figsize=(15,5))
for i in range(nets):
    plt.plot(history[i].history['val_acc'],linestyle=styles[i])
plt.title('model accuracy')
plt.ylabel('accuracy')
plt.xlabel('epoch')
plt.legend(names, loc='upper left')
axes = plt.gca()
axes.set_ylim([0.98,1])
plt.show()
```

## Feature maps

## Dense layer

## Dropout

## Advance
* Replace **P2** with **C5S2** to make it learnable. 
* Add batch normalization.
* Add image data augmentation
```python
# CREATE MORE TRAINING IMAGES VIA DATA AUGMENTATION
datagen = ImageDataGenerator(
        rotation_range=10,  
        zoom_range = 0.1,  
        width_shift_range=0.1, 
        height_shift_range=0.1)
# TRAIN NETWORK 5
j = nets-1
history[j] = model[j].fit_generator(datagen.flow(X_train2,Y_train2, batch_size=64), 
    epochs = epochs, steps_per_epoch = X_train2.shape[0]//64,
    validation_data = (X_val2,Y_val2), callbacks=[annealer], verbose=0)
print("CNN {0}: Epochs={1:d}, Train accuracy={2:.5f}, Validation accuracy={3:.5f}".format(
    names[j],epochs,max(history[j].history['acc']),max(history[j].history['val_acc']) ))
```
