from tensorflow.keras.preprocessing import image
from tensorflow.keras.preprocessing.image import ImageDataGenerator
import tensorflow as tf
import numpy as np

img_size = (224, 224)
train_dir = 'train' 
train_datagen = ImageDataGenerator(
    rescale=1./255,               # Normalize pixel values to [0, 1]
    rotation_range=30,            # Random rotations from -30 to +30 degrees
    width_shift_range=0.2,        # Random horizontal shifts
    height_shift_range=0.2,       # Random vertical shifts
    shear_range=0.2,              # Random shear
    zoom_range=0.2,               # Random zoom
    horizontal_flip=True,         # Random horizontal flip
    fill_mode='nearest'           # Fill pixels after transformation
)
train_generator = train_datagen.flow_from_directory(
    train_dir,                    # Path to training directory
    target_size=img_size,         # Resize all images to 224x224
    batch_size=32,                # Number of images per batch
    class_mode='categorical',     # Use categorical for multi-class classification
    shuffle=True                  # Shuffle training data
)
# Load the saved model
model = tf.keras.models.load_model('final.h5')
def predict_image(image_path):
    img = image.load_img(image_path, target_size=(224, 224))  # Resize the image
    img_array = image.img_to_array(img)  # Convert image to array
    img_array = np.expand_dims(img_array, axis=0)  # Add batch dimension
    img_array = img_array / 255.0  # Normalize image
    
    # Predict the class
    predictions = model.predict(img_array)
    class_idx = np.argmax(predictions[0])  # Get the index of the highest prediction
    class_label = list(train_generator.class_indices.keys())[class_idx]  # Get the class label
    
    #print(f"Predicted class: {class_label}")
    predicted_class = class_label
    return class_label

predicted_class = predict_image('captured_images/captured_image.jpg')  #need to change captured_images/captured_image.jpg
#predicted_class = predict_image('bottle.jpg')
#print(predicted_class)