# Helpful tips

* Random negative images source: https://source.unsplash.com/random/1280x640

* Count all the files in a directory. Useful when wanting to know how many positive or negative images you have: 

  ```ls -1 | wc -l```

* Move files from subdirectories into a single folder

  ```find /mnt/d/Keut/Downloads/vision\ personen/ -type f -print0 | xargs -0 mv -t /mnt/d/Keut/Downloads/vision\ personen\ single\ folder/```

* Start annotating positive images

  ```opencv_annotation --annotations=annotations.txt --images=positive/ --maxWindowHeight=800 --resizeFactor=5```

* Create a collection file from the negative images

  ```find ../../data/negatives/ -name '*.jpg' > negatives.dat```

* When getting error: `images/annotations.txt(101) : parse errorInfo file name: images/annotations.txt`

  Add `-num 100` to the end of the command, possibly because it reads an empty line at the end of annotations.txt

* Big help: http://note.sonots.com/SciSoftware/haartraining.html

* Train the set

  `opencv_traincascade -data xml/ -vec samples.vec -bg images/negatives.dat -numStages 20 -minHitRate 0.999 -maxFalseAlarmRate 0.5 -numPos 100 -numNeg 100 -w 20 -h 20 -mode ALL`

* Why does the opencv_traincascade not train all the stages:  http://answers.opencv.org/question/84852/traincascades-error-required-leaf-false-alarm-rate-achieved-branch-training-terminated/
