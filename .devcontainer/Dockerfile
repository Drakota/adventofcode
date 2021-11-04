FROM continuumio/miniconda3

# [Option] Install zsh
ARG INSTALL_ZSH="true"
# [Option] Upgrade OS packages to their latest versions
ARG UPGRADE_PACKAGES="true"

# Install needed packages and setup non-root user. Use a separate RUN statement to add your own dependencies.
ENV USERNAME=code
ENV USER_UID=1000
ENV USER_GID=$USER_UID

# Python arguments
ARG PIPX_HOME=/usr/local/py-utils
ARG PIPX_BIN_DIR=/usr/local/py-utils/bin
ENV PATH=$PATH:$PIPX_BIN_DIR

# Rust & Cargo arguments
ARG RUSTUP_HOME=/usr/local/rustup
ARG CARGO_HOME=/usr/local/cargo
ARG RUST_VERSION=1.56.1
ENV PATH=/usr/local/cargo/bin:$PATH

COPY scripts/*.sh /tmp/scripts/
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    # Install common packages, non-root user, update yarn and install nvm
    && bash /tmp/scripts/common.sh "$INSTALL_ZSH" "$USERNAME" "$USER_UID" "$USER_GID" "$UPGRADE_PACKAGES" \
    # Install conda and pipx
    && bash /tmp/scripts/python.sh "none" "/opt/conda" "$PIPX_HOME" "$USERNAME" "false" \
    # Install rust toolchain & cargo
    && bash /tmp/scripts/rust.sh "$CARGO_HOME" "$RUSTUP_HOME" "$USERNAME" "true" "true" \
    # Clean up
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/* /root/.gnupg /tmp/scripts

RUN mkdir /opt/conda/pkgs && \
    touch /opt/conda/pkgs/urls.txt && \
    chown -R $USER_UID:$USER_GID /opt/conda

CMD ["sleep", "infinity"]