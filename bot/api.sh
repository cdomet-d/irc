#!/bin/bash

curl -X POST --data "grant_type=client_credentials&client_id=u-s4t2ud-ad20c0580b5b2d1e67736549dd536f87146a2340a5cbd41aba0c1da8655e0293&client_secret=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" https://api.intra.42.fr/oauth/token | jq

