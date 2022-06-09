#!/bin/bash

awk '{sum += $2} END{print sum / NR}' ps.fake
