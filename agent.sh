#!/bin/bash
# Adds ssh agent to bash

eval `ssh-agent`
ssh-add ~/.ssh/id_rsa

