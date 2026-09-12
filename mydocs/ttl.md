# TTL

TTL = **Time To Live**

It means a key can automatically expire after a given amount of time.

## Syntax

```text
SET key value
SET key value ttl
```

Example:

```text
SET name anup
SET name anup 10
```

The second one means `name` will expire after **10 seconds**.

## How it works

When we set a TTL, we don't store only the value.

We store:

```text
value
expiry time
hasExpiry
```

For example:

```text
SET name anup 10
```

We calculate:

```text
expiry = current time + 10 seconds
```

When `GET` or `EXISTS` is called, we check:

```text
current time >= expiry
```

If expired:

```text
delete key
```

Otherwise return/use the key normally.

## Lazy Expiration

We use **lazy expiration**.

We don't continuously check all keys in the background.

We check expiration only when the key is accessed using `GET` or `EXISTS`.

This keeps the implementation simple and avoids an extra background thread.
