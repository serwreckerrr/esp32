import pandas as pd
import numpy as np

# Load your raw CSV
df = pd.read_csv("sensor_data.csv", names=["temp", "humidity", "label"])

# Sort for stable filtering
df = df.sort_values(["temp", "humidity"]).reset_index(drop=True)

# Thresholds for "too close"
TEMP_EPS = 0.5
HUM_EPS = 5.0

cleaned = []
prev_t = None
prev_h = None
prev_label = None

for i, row in df.iterrows():
    t = row["temp"]
    h = row["humidity"]
    lbl = row["label"]

    # First row always kept
    if prev_t is None:
        cleaned.append(row)
        prev_t, prev_h, prev_label = t, h, lbl
        continue

    # Check closeness
    if abs(t - prev_t) < TEMP_EPS and abs(h - prev_h) < HUM_EPS:
        # Too close → skip this row
        continue

    # Otherwise keep row
    cleaned.append(row)
    prev_t, prev_h, prev_label = t, h, lbl

# Convert cleaned list to DataFrame
cleaned_df = pd.DataFrame(cleaned)

# Save cleaned dataset
cleaned_df.to_csv("sensor_data_cleaned.csv", index=False, header=False)

print("Original size:", len(df))
print("Cleaned size :", len(cleaned_df))
print("Removed      :", len(df) - len(cleaned_df))
