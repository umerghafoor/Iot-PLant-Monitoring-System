
## print from this file cert_path = "../AWS data/Device Certificate.crt"
import os

print(os.path.abspath("AWS data/Device Certificate.crt"))  # Output: /home/runner/Dashboard/AWS data/Device Certificate.crt
print(os.path.exists("AWS data/Device Certificate.crt"))  # Output: False