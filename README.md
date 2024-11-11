# Unit Testing Suite For DHCP4 HAL

The following documents should be referenced to provide specific information on the tests required for this module.

## Table of Contents

- [Version History](#version-history)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Description](#description)
- [Reference Documents](#reference-documents)

## Version History

| Date | Comment | Version |
| --- | --- | --- |
| 07/30/24 | Initial Release | 1.0.0 |

## Acronyms, Terms and Abbreviations

- `L1` - Unit Tests
- `HAL`- Hardware Abstraction Layer

## Description

This repository contains the Unit Test Suites L1 for DHCP4 HAL.

## Testing Environment

### Build the linux environment from hal repo :

```bash
./build_ut.sh
```

### Build the target `crosscompile` environment from hal repo :

- For building `dhcpv4c_api` :
```bash
./build_ut.sh TARGET=`crosscompile` HAL=dhcpv4c_api
```

- For building `dhcp4cApi` :

Set the crosscompile environment
```bash
./build_ut.sh TARGET=`crosscompile` HAL=dhcp4cApi
```
let `crosscompile' is the target environment like arm ,intel ...

## Reference Documents

|SNo|Document Name|Document Description|Document Link|
|---|-------------|--------------------|-------------|
|1|`HAL` Specification Document|This document provides specific information on the APIs for which tests are written in this module|[DHCPv4ChalSpec.md](../../../../../rdkcentral/rdkb-halif-dhcp/blob/main/docs/pages/DHCPv4ChalSpec.md "DHCPv4ChalSpec.md")|
|2|`L1` Tests | `L1` Test Case File for dhcpv4c_api header |[test_l1_dhcpv4c_api.c](src/test_l1_dhcpv4c_api.c "test_l1_dhcpv4c_api.c")|
|3|`L1` Tests | `L1` Test Case File for dhcp4cApi header |[test_l1_dhcp4cApi.c](src/test_l1_dhcp4cApi.c "test_l1_dhcp4cApi.c")|