# Postgres Base58 Codec Functions

## Usage
```
postgres=# select base58_encode('ccb36a53-8e1b-4166-a128-4fae70604c93'::uuid);
     base58_encode      
------------------------
 rh5WUJhkExvBDL6ZuXKyXV
(1 row)

postgres=# select base58_decode(base58_encode('ccb36a53-8e1b-4166-a128-4fae70604c93'::uuid));
            base58_decode             
--------------------------------------
 ccb36a53-8e1b-4166-a128-4fae70604c93
(1 row)

postgres=# select base58_encode(base58_decode(base58_encode('ccb36a53-8e1b-4166-a128-4fae70604c93'::uuid)));
     base58_encode      
------------------------
 rh5WUJhkExvBDL6ZuXKyXV
(1 row)
```
