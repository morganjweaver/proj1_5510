#!/bin/bash

#scp -i ~/.ssh/id_rsa ../* weaverm1@cs1.seattleu.edu:~/proj1/

scp -r ../proj1_5510 weaverm1@cs1.seattleu.edu:~/proj1/

echo "transferred to cs1"

#scp weaverm1@cs1.seattleu.edu: ~/proj1/proj1_5510/server weaverm1@cs2.seattleu.edu:proj1/ 

ssh -i ~/.ssh/id_rsa weaverm1@cs1.seattleu.edu "scp ~/proj1/proj1_5510/server weaverm1@cs2.seattleu.edu:proj1/" 


echo "\n done!"


