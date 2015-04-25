# Weird Issues
- See Sean's note about the LM in the readme in the main directory.

- During tuning, you will need to hack the moses ini file to add the input
  weight. Look for the appropriate ini file (something like
  `tuning/moses.filtered.ini.XX`) and add the following:

  Under the `[feature]` heading:

  ```
  InputFeature num-features=1 num-input-features=1 real-word-count=0
  ```

  Under the `[weight]` heading:
  
  ```
  InputFeature0= 1
  ```
