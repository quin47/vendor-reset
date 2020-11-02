/*
Vendor Reset - Vendor Specific Reset
Copyright (C) 2020 Geoffrey McRae <geoff@hostfission.com>
Copyright (C) 2020 Adam Madsen <adam@ajmadsen.com>

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA
*/

#ifndef _H_VENDOR_RESET_DEV
#define _H_VENDOR_RESET_DEV

#define VENDOR_RESET_DEVICE_ALL ((unsigned int)-1)

#include <linux/pci.h>

struct vendor_reset_dev
{
  struct pci_dev *pdev;

  int reset_ret;

  void *vendor_private;
};

struct vendor_reset_ops
{
  /* any pre-reset ops to do, i.e., common code between devices */
  int (*pre_reset)(struct vendor_reset_dev *);
  /* the reset method for the device at the specified address */
  int (*reset)(struct vendor_reset_dev *);
  /* any post-reset ops to do, i.e., common code between devices */
  int (*post_reset)(struct vendor_reset_dev *);
};

struct vendor_reset_cfg
{
  /* the vendor ID */
  unsigned int vendor;

  /* the device ID or VENDOR_RESET_DEVICE_ALL to match all devices for the
   * vendor */
  unsigned int device;

  /* the reset operations */
  const struct vendor_reset_ops * ops;
};

#endif